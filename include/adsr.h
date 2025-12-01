//
// Created by Mitch on 1/12/2025.
//

#ifndef CPP_ENGINEERING_ADSR_H
#define CPP_ENGINEERING_ADSR_H
#include <cstdint>

#include "q8_8.h"


class adsr {
    public:
    enum class State {
        Idle,
        Attack,
        Decay,
        Sustain,
        Release
    };

    adsr() = default;

    void set_sample_rate(uint32_t sample_rate);

    void set_attack(float ms);
    void set_decay(float ms);
    void set_release(float ms);

    void set_sustain_level(float level);

    void set_attack_samples(uint32_t samples);
    void set_decay_samples(uint32_t samples);
    void set_release_samples(uint32_t samples);

    void noteOn();

    void noteOff();

    q8_8 next();

    [[nodiscard]] State state() const noexcept { return state_; }

    [[nodiscard]] bool isActive() const noexcept { return state_ != State::Idle; }
    [[nodiscard]] q8_8 level() const noexcept { return level_; }

private:
    // Sample rate for ms → samples conversion
    uint32_t sample_rate_ = 48000;

    // Stage durations in samples
    uint32_t attack_samples_  = 0;
    uint32_t decay_samples_   = 0;
    uint32_t release_samples_ = 0;

    // Sustain level in Q8.8 (0..256)
    q8_8 sustain_level_ = q8_8::q8_8_fromFloat(0.0); // default full level

    // Current envelope level in Q8.8 (0..256)
    q8_8 level_ = q8_8::q8_8_fromFloat(0.0);

    // One step per stage in Q8.8.
    // You can recompute this when entering each stage:
    //   step = (target - start) / duration_in_samples
    q8_8 attack_step_  = q8_8::q8_8_fromFloat(0.0);
    q8_8 decay_step_  = q8_8::q8_8_fromFloat(0.0);
    q8_8 release_step_ = q8_8::q8_8_fromFloat(0.0);

    // How many samples we’ve spent in the current stage
    uint32_t stage_samples_elapsed_ = 0;

    // Current state
    State state_ = State::Idle;

    [[nodiscard]] uint32_t convert_ms_to_samples(float ms) const;

    void enter_idle();
    void enter_attack();
    void update_attack();
    void enter_decay();
    void update_decay();
    void enter_sustain();
    void update_sustain();
    void enter_release();
    void update_release();
};


#endif //CPP_ENGINEERING_ADSR_H