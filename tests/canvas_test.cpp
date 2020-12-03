#include <catch2/catch.hpp>
#include <vector>
#include "cinder/gl/gl.h"
#include "canvas.h"

using namespace starfall;

TEST_CASE("Test whether star is at canvas boundary") {
    Canvas test_canvas(glm::vec2(50, 50),
                       200, 200);

    test_canvas.AddPointToBoundaries(glm::vec2(55, 55));

    SECTION("Star hits boundary") {
        ShootingStar star(glm::vec2(54, 54),
                          ci::Color(0, 255, 0), M_PI / 4);

        REQUIRE(test_canvas.IsStarDisappearingBehindBoundary(star));
    }

    SECTION("Star is outside boundary") {
        ShootingStar star_2(glm::vec2(55, 58),
                            ci::Color(0, 255, 0), M_PI / 4);
        REQUIRE_FALSE(test_canvas.IsStarDisappearingBehindBoundary(star_2));
    }
}

TEST_CASE("Star progressive disappears after hitting boundary") {
    Canvas test_canvas(glm::vec2(50, 50),
                       200, 200);
    ShootingStar star(glm::vec2(54, 54),
                      ci::Color(0, 255, 0), M_PI / 4);

    test_canvas.AddPointToBoundaries(glm::vec2(55, 55));

    REQUIRE(test_canvas.IsStarDisappearingBehindBoundary(star));
}

TEST_CASE("Test Deleting Star After Drawn Boundary Collision") {
    Canvas test_canvas(glm::vec2(50, 50),
                       200, 200);
    ShootingStar star(glm::vec2(53, 53),
                      ci::Color(0, 255, 0), M_PI / 4);

    test_canvas.AddPointToBoundaries(glm::vec2(56, 56));

    test_canvas.AddStarToList(star);
    REQUIRE_FALSE(test_canvas.IsStarDisappearingBehindBoundary(test_canvas.GetStarList()[0]));
    test_canvas.Update();
    REQUIRE(test_canvas.IsStarDisappearingBehindBoundary(test_canvas.GetStarList()[0]));

    SECTION("Star Hits Boundary and is Updated to Disappear") {
        test_canvas.Update();
        test_canvas.Update();
        test_canvas.Update();
        REQUIRE(test_canvas.GetStarList().empty());
    }

}

TEST_CASE("Test Deleting Star After Star Falls Out of Bounds") {
    Canvas test_canvas(glm::vec2(50, 50),
                       200, 200);

    SECTION("Star is initialized at boundary") {
        // the last center of the last circle that makes up the tail will be at (250, 55)
        ShootingStar star(glm::vec2(250, 55),
                          ci::Color(0, 255, 0), 0);


        test_canvas.AddStarToList(star);
        test_canvas.Update();

        REQUIRE(test_canvas.GetStarList().empty());
    }

    SECTION("Star moves out of bounds") {
        ShootingStar star(glm::vec2(248, 55),
                          ci::Color(0, 255, 0), 0);

        // the last center of the last circle that makes up the tail will be at (250, 55)
        for (size_t i = 0; i < 16; i++) {
            test_canvas.Update();
        }

        // this update should delete star
        test_canvas.Update();
        REQUIRE(test_canvas.GetStarList().empty());
    }
}

TEST_CASE("Add Point to Boundary Map") {
    Canvas test_canvas(glm::vec2(50, 50),
                       200, 200);
    SECTION("Add 1 point") {
        test_canvas.AddPointToBoundaries(glm::vec2(55, 55));
    }

    SECTION("Add 2 points with the same x value") {
        test_canvas.AddPointToBoundaries(glm::vec2(55, 55));
        test_canvas.AddPointToBoundaries(glm::vec2(55, 56));
    }

}