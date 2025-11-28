//
// Created by Mitch on 28/11/2025.
//

#include "../include/q8_8.h"

#include <algorithm>
#include <cmath>

// Default constructor
q8_8::q8_8() {
    this->value = 0;
}

q8_8::q8_8(const int16_t v) {
    this->value = v;
}

float q8_8::toFloat() const {
    return this->value / 256.0f;
}

q8_8 q8_8::operator+(const q8_8& other) const {
    int32_t wide = this->value + other.value;
    wide = std::clamp(wide, -32768, 32767);

    return q8_8(static_cast<int16_t>(wide));
}

q8_8 q8_8::operator-(const q8_8& other) const {
    int32_t wide = this->value - other.value;
    wide = std::clamp(wide, -32768, 32767);

    return q8_8(static_cast<int16_t>(wide));
}

q8_8 q8_8::operator*(const q8_8& other) const {
    int32_t wide = this->value * other.value;
    wide = std::clamp(wide, -32768, 32767);
    return q8_8(static_cast<int16_t>(wide));
}

q8_8 q8_8::operator/(const q8_8& other) const {
    int32_t wide = this->value / other.value;
    wide= std::clamp(wide, -32768, 32767);
    return q8_8(static_cast<int16_t>(wide));
}

q8_8 q8_8::q8_8_fromFloat(float f) {
    auto wide = static_cast<int32_t>(f * 256.0f);
    wide = std::lround(wide);
    wide = std::clamp(wide, -32768, 32767);
    return q8_8(static_cast<int16_t>(wide));
}




