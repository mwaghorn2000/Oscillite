//
// Created by Mitch on 28/11/2025.
//

#ifndef CPP_ENGINEERING_Q8_8_H
#define CPP_ENGINEERING_Q8_8_H
#include <cstdint>


class q8_8 {
private:
    int16_t value;

public:
    q8_8();
    explicit q8_8(int integer);
    static q8_8 q8_8_fromFloat(float f);

    [[nodiscard]] float toFloat() const;
    q8_8 operator+(const q8_8 & other) const;
    q8_8 operator-(const q8_8 & other) const;
    q8_8 operator*(const q8_8 & other) const;
    q8_8 operator/(const q8_8 & other) const;

    [[nodiscard]] int16_t raw() const { return value; }
};


#endif //CPP_ENGINEERING_Q8_8_H