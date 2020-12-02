#include <catch2/catch.hpp>
#include <vector>
#include "cinder/gl/gl.h"
#include "canvas.h"

using namespace starfall;

TEST_CASE("Test whether star is at canvas boundary") {
    Canvas test_canvas(glm::vec2(50, 50),
            200, 50);

    test_canvas.AddPointToBoundaries(glm::vec2(55, 55));

    SECTION("Star hits boundary") {
        ShootingStar star(glm::vec2(54, 54),
                          ci::Color(0, 255, 0), M_PI / 4);

        REQUIRE(test_canvas.IsStarDisappearing(star));
    }

    SECTION("Star is outside boundary") {
        ShootingStar star_2(glm::vec2(55, 58),
                            ci::Color(0, 255, 0), M_PI / 4);
        REQUIRE_FALSE(test_canvas.IsStarDisappearing(star_2));
    }
}

TEST_CASE("Star progressive disappears after hitting boundary") {
    Canvas test_canvas(glm::vec2(50, 50),
                       200, 50);
    ShootingStar star(glm::vec2(54, 54),
                      ci::Color(0, 255, 0), M_PI / 4);

    test_canvas.AddPointToBoundaries(glm::vec2(55, 55));

    REQUIRE(test_canvas.IsStarDisappearing(star));
}

TEST_CASE("Test Deleting Star After Boundary Collision") {
    Canvas test_canvas(glm::vec2(50, 50),
                       200, 50);
    ShootingStar star(glm::vec2(53, 53),
                      ci::Color(0, 255, 0), M_PI / 4);

    test_canvas.AddPointToBoundaries(glm::vec2(55, 55));

    test_canvas.AddStarToList(star);
    REQUIRE_FALSE(test_canvas.IsStarDisappearing(test_canvas.GetStarList()[0]));
    test_canvas.Update();
    REQUIRE(test_canvas.IsStarDisappearing(test_canvas.GetStarList()[0]));

    SECTION("Star Hits Boundary and is Updated to Disappear") {
        test_canvas.Update();
        test_canvas.Update();
        REQUIRE(test_canvas.GetStarList().empty());
    }

}