//
// Created by Mitch on 29/11/2025.
//

#ifndef CPP_ENGINEERING_SIN_H
#define CPP_ENGINEERING_SIN_H
#include <cstdint>
#include <math.h>

#include "q8_8.h"


class func_g {
public:
    struct Osc {
        float phase;        // [0, 1]
        float phase_inc;    // f / sampleRate
    };

    explicit func_g(float sample_rate);

    void set_frequency(float freq);

    q8_8 next_sample();

private:
    // precompute PI
    static constexpr float TWO_PI = 6.28318530717958647692f;

    float sample_rate_;
    Osc osc_{};
};

#endif //CPP_ENGINEERING_SIN_H