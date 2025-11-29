//
// Created by Mitch on 29/11/2025.
//

#include "../include/func_g.h"
#include <cmath>
#include <iostream>

func_g::func_g(const float sample_rate) : sample_rate_(sample_rate) {
    osc_.phase = 0.0f;
    osc_.phase_inc = 0.0f;
}

void func_g::set_frequency(const float freq) {
    osc_.phase_inc = freq / sample_rate_;
}

q8_8 func_g::next_sample() {
    osc_.phase += osc_.phase_inc;

    if (osc_.phase >= 1.0f) {
        osc_.phase -= 1.0f;
    }

    const float y = sinf(osc_.phase * TWO_PI); // y in [-1, 1]
    const auto s = q8_8::q8_8_fromFloat(y);
    std::cout << s.toFloat() << "\n";
    return s;
}


