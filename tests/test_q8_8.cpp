//
// Created by Mitch on 1/12/2025.
//

#include "q8_8.h"
#include "../cmake-build-debug/_deps/catch2-src/src/catch2/catch_test_macros.hpp"

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
