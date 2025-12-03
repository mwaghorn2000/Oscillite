//
// Created by Mitch on 1/12/2025.
//

#include <cmath>

#include "q8_8.h"
#include <catch2/catch_test_macros.hpp>

const float eps = 0.0001f;

TEST_CASE("Default constructor") {
    auto x = q8_8();
    REQUIRE(x.toFloat() == 0);
}

TEST_CASE("Q8_8 from float") {
    const auto x = q8_8::q8_8_fromFloat(10.5f);
    constexpr int16_t expected = 0x0A80;
    REQUIRE(x.raw() == expected);
}

TEST_CASE("Q8_8 from int") {
    const auto x = q8_8::q8_8_FromInt(32);
    int16_t expected = 0x2000;
    REQUIRE(x.raw() == expected);

    const auto y = q8_8::q8_8_FromInt(-96);
    expected = 0xA000;
    REQUIRE(y.raw() == expected);
}

TEST_CASE("Addition") {
    const auto x = q8_8::q8_8_fromFloat(1.5);
    const auto y = q8_8::q8_8_fromFloat(-26.5);

    constexpr float expected = -25.0f;
    REQUIRE((x + y).toFloat() == expected);
}

TEST_CASE("Subtraction") {
    const auto x = q8_8::q8_8_fromFloat(4.25);
    const auto y = q8_8::q8_8_fromFloat(-26.5);

    constexpr float expected = 30.75;
    REQUIRE((x - y).toFloat() == expected);
}

TEST_CASE("Multiplication") {
    const auto x = q8_8::q8_8_fromFloat(4.25f);
    const auto y = q8_8::q8_8_fromFloat(2.5f);

    constexpr float expected = 10.625;
    REQUIRE((x * y).toFloat() == expected);
}

TEST_CASE("Division") {
    const auto x = q8_8::q8_8_fromFloat(4.25f);
    const auto y = q8_8::q8_8_fromFloat(2.5f);

    const auto result = x / y;
    constexpr float expected = 1.7f;
    REQUIRE((result.toFloat() - expected) <= eps);
}

TEST_CASE("RAW") {
    const auto x = q8_8::q8_8_fromFloat(4.25f);
    const auto y = x.raw();

    REQUIRE(y == 0x0440);
}

TEST_CASE("Clamping Positive") {
    const auto x = q8_8::q8_8_fromFloat(120.0f);
    const auto y = q8_8::q8_8_fromFloat(20.0f);

    REQUIRE(fabsf((x+y).toFloat() - 127.9961f) <= eps );
}

TEST_CASE("Clamping Negative") {
    const auto x = q8_8::q8_8_fromFloat(-120.0f);
    const auto y = q8_8::q8_8_fromFloat(-20.0f);

    REQUIRE(fabsf((x+y).toFloat() + 128.0f) <= eps );
}
