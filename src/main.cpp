#include <cassert>
#include <complex>
#include <iostream>
#include <q8_8.h>

void q8_8_tests();
void test_framework(float E, float R);

int main() {
    std::cout << "Hello C++ development environment!" << std::endl;
    std::cout << "Running Tests!..." << std::endl;
    q8_8_tests();
    return 0;
}

void q8_8_tests() {
    q8_8 test = q8_8(0x0180);
    float result = test.toFloat();
    float expected = 1.5f;
    test_framework(expected, result);

    test = q8_8(0x4061);
    result = test.toFloat();
    expected = 64.3789;
    test_framework(expected, result);

    test = q8_8(0xFE00);
    result = test.toFloat();
    expected = -2.0f;
    test_framework(expected, result);

    test = q8_8(0x0180);
    const q8_8 sum = test + test;
    result = sum.toFloat();
    expected = 3.0f;
    test_framework(expected, result);
}

void test_framework(const float E, const float R) {
    static constexpr float EPS = 0.0001f;
    std::cout << "R: " << R << " E: " << E;
    if (std::fabs(R - E) > EPS) {
        assert(false);
    }
    std::cout << " ....   Passed" << std::endl;
}