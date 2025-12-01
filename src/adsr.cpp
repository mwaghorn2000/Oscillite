//
// Created by Mitch on 1/12/2025.
//

#include "../include/adsr.h"

void adsr::set_sample_rate(const uint32_t sample_rate) {
    sample_rate_ = sample_rate;
}

void adsr::set_attack(const float ms) {
    adsr::set_attack_samples(convert_ms_to_samples(ms));
}

void adsr::set_attack_samples(uint32_t samples) {
    attack_samples_ = samples;
}

void adsr::set_decay(const float ms) {
    adsr::set_decay_samples(convert_ms_to_samples(ms));
}

void adsr::set_decay_samples(uint32_t samples) {
    decay_samples_ = samples;
}

void adsr::set_release(float ms) {
    adsr::set_release_samples(convert_ms_to_samples(ms));
}

void adsr::set_release_samples(const uint32_t samples) {
    release_samples_ = samples;
}

void adsr::set_sustain_level(float level) {
    if (level < 0.0) level = 0.0f;
    if (level > 1.0) level = 1.0f;
    sustain_level_ = q8_8::q8_8_fromFloat(level);
}

q8_8 adsr::next() {
    switch (state_) {
        case State::Idle:
            return q8_8::q8_8_FromInt(0);
        case State::Attack:
            update_attack();
            break;
        case State::Decay:
            update_decay();
            break;
        case State::Sustain:
            update_sustain();
            break;
        case State::Release:
            update_release();
            break;
    }

    return level_;
}

uint32_t adsr::convert_ms_to_samples(const float ms) const {
    const float seconds = ms /1000.0f;
    const float samples_f = seconds * static_cast<float>(sample_rate_);
    return static_cast<uint32_t>(samples_f);
}

void adsr::enter_attack() {
    state_ = State::Attack;
    stage_samples_elapsed_ = 0;
    if (attack_samples_ == 0) {
        level_ = q8_8::q8_8_fromFloat(1.0f);
        enter_decay();
        return;
    }
    attack_step_ = q8_8::q8_8_fromFloat((1.0f - level_.toFloat()) / attack_samples_);
}

void adsr::update_attack() {
    level_ = level_ + attack_step_;
    stage_samples_elapsed_++;
    if (stage_samples_elapsed_ >= attack_samples_) {
        level_ = q8_8::q8_8_fromFloat(1.0f);
        enter_decay();
    }
}

void adsr::enter_decay() {
    state_ = State::Decay;
    stage_samples_elapsed_ = 0;
    if (decay_samples_ == 0) {
        level_ = sustain_level_;
        enter_sustain();
        return;
    }
    decay_step_ = q8_8::q8_8_fromFloat((sustain_level_-level_).toFloat() / decay_samples_);
}

void adsr::update_decay() {
    level_ = level_ + decay_step_;
    stage_samples_elapsed_++;
    if (stage_samples_elapsed_ >= decay_samples_) {
        level_ = sustain_level_;
        enter_sustain();
    }
}

void adsr::enter_sustain() {
    state_ = State::Sustain;
    stage_samples_elapsed_ = 0;
    level_ = sustain_level_;
}

void adsr::update_sustain() {
    // do nothing
    // state will update when note is released
}

void adsr::enter_release() {
    state_ = State::Release;
    stage_samples_elapsed_ = 0;
    if (release_samples_ == 0) {
        level_ = q8_8::q8_8_fromFloat(0.0f);
        enter_idle();
        return;
    }

    release_step_ = q8_8::q8_8_fromFloat((0-level_.toFloat()) / release_samples_);
}

void adsr::update_release() {
    level_ = level_ + release_step_;
    stage_samples_elapsed_++;
    if (stage_samples_elapsed_ >= release_samples_ || level_.toFloat() <= 0.0f) {
        enter_idle();
    }
}

void adsr::enter_idle() {
    state_ = State::Idle;
    level_ = q8_8();
    stage_samples_elapsed_ = 0;
}

void adsr::noteOn() {
    enter_attack();
}

void adsr::noteOff() {
    if (state_ != State::Idle && state_ != State::Release) {
        enter_release();
    }
}





