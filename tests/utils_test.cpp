#include <catch2/catch.hpp>
#include "cinder/gl/gl.h"
#include "utils.h"

using namespace starfall;

TEST_CASE("Test Get Random Float") {
    float previous_float = 1.0f;

    // There is always the possibility that the same number
    // will be randomly generated twice, but that probability is
    // so low for only 20 values.
    for (size_t i = 0; i < 20; i++) {
        // random_float will never be 1
        float random_float = GetRandomFloat(0, 1);
        REQUIRE(random_float != previous_float);
        previous_float = random_float;
    }
}

TEST_CASE("Test Get Random Int") {
    int previous_int = 201;

    // There is always the possibility that the same number
    // will be randomly generated twice, but that probability is
    // so low for only 20 values.
    for (size_t i = 0; i < 20; i++) {
        // random_float will never be 201
        int random_int = GetRandomFloat(0, 200);
        REQUIRE(random_int != previous_int);
        previous_int = random_int;
    }
}