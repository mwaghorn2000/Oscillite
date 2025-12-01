//
// Created by Mitch on 29/11/2025.
//

#ifndef CPP_ENGINEERING_SIN_H
#define CPP_ENGINEERING_SIN_H
#include <cstdint>
#include <math.h>

#include "q8_8.h"

namespace dsp {

    struct Waveform {
        enum class Kind {Sine, Square, Saw, Triangle};


        Kind kind;
        float pwm;

        static Waveform sine() {
            return { Kind::Sine, 0.5f };
        }

        static Waveform saw() {
            return { Kind::Saw, 0.0f };
        }

        static Waveform triangle() {
            return {Kind::Triangle, 0.0f};
        }

        static Waveform square(const float pwm = 0.5f) {
            return {Kind::Square, pwm};
        }

    };

    class oscillator {
    public:
        explicit oscillator(float sample_rate, float freq, Waveform wf)
            : sample_rate_(sample_rate),
              phase_(0.0f),
              phase_inc_(freq/sample_rate),
              waveform_(wf) {}

        void set_frequency(float freq);
        void set_waveform(Waveform wf);

        q8_8 next_sample();

    private:
        // precompute PI
        static constexpr float TWO_PI = 6.28318530717958647692f;

        float sample_rate_{};
        float phase_{};
        float phase_inc_{};
        float pwm_{};
        Waveform waveform_;

    };


}



#endif //CPP_ENGINEERING_SIN_H