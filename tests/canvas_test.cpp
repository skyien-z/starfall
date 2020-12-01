#include <catch2/catch.hpp>
#include <vector>
#include "cinder/gl/gl.h"
#include "canvas.h"

using namespace starfall;

TEST_CASE("Test whether star is at canvas boundary") {
    Canvas test_canvas(glm::vec2(50, 50),
            200, 50);
    ShootingStar star(glm::vec2(54, 54),
                      ci::Color(0, 255, 0), M_PI / 4);

    test_canvas.AddPointToBoundaries(glm::vec2(55, 55));

    REQUIRE(test_canvas.IsStarAtBoundary(star));
}

TEST_CASE("Test star hitting boundary deletion") {
    Canvas test_canvas(glm::vec2(50, 50),
                       200, 50);
    ShootingStar star(glm::vec2(54, 54),
                      ci::Color(0, 255, 0), M_PI / 4);

    test_canvas.AddPointToBoundaries(glm::vec2(55, 55));

    REQUIRE(test_canvas.IsStarAtBoundary(star));
}