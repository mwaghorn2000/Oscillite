//
// Created by Mitch on 28/11/2025.
//

#include "../include/q8_8.h"

#include <algorithm>
#include <cassert>
#include <cmath>

// Default constructor
q8_8::q8_8() {
    this->value = 0;
}

q8_8 q8_8::q8_8_FromInt(int integer) {
    int32_t wide = static_cast<int32_t>(integer) << 8;
    wide = std::clamp(wide, -32768, 32767);
    return q8_8(static_cast<int16_t>(wide));
}

float q8_8::toFloat() const {
    return this->value / 256.0f;
}

q8_8 q8_8::operator+(const q8_8& other) const {
    int32_t wide = static_cast<int32_t>(this->value) + static_cast<int32_t>(other.value);
    wide = std::clamp(wide, -32768, 32767);

    return q8_8(static_cast<int16_t>(wide));
}

q8_8 q8_8::operator-(const q8_8& other) const {
    int32_t wide = static_cast<int32_t>(this->value) - static_cast<int32_t>(other.value);
    wide = std::clamp(wide, -32768, 32767);

    return q8_8(static_cast<int16_t>(wide));
}

q8_8 q8_8::operator*(const q8_8& other) const {
    int32_t wide = (static_cast<int32_t>(this->value) * static_cast<int32_t>(other.value)) >> 8;
    wide = std::clamp(wide, -32768, 32767);
    return q8_8(static_cast<int16_t>(wide));
}

q8_8 q8_8::operator/(const q8_8& other) const {
    if (other.toFloat() == 0.0) {
        return q8_8(0);
    }
    const auto a = static_cast<int32_t>(this->value);
    const auto b = static_cast<int32_t>(other.value);
    int32_t wide = (a << 8) / b;
    wide= std::clamp(wide, -32768, 32767);
    return q8_8(static_cast<int16_t>(wide));
}

q8_8 q8_8::q8_8_fromFloat(float f) {
    // scale by 2^8 = 256 for Q8.8
    float scaled = f * 256.0f;
    auto wide = static_cast<int32_t>(std::lround(scaled));

    // Saturation to int16 range (this will NOT trigger for f in [-1, 1])
    if (wide < -32768) wide = -32768;
    if (wide >  32767) wide =  32767;

    return q8_8(static_cast<int16_t>(wide));
}



