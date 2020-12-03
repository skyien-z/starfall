#include <catch2/catch.hpp>
#include <vector>
#include "cinder/gl/gl.h"
#include "canvas.h"

using namespace starfall;

const int kMoveByX = 2;

TEST_CASE("Does Star Touch Point") {
    // radius of all stars is 2

    ShootingStar star(glm::vec2(50, 50),
                      ci::Color(0, 255, 0), M_PI / 4);

    SECTION("Horizontal Position Difference; touch on edge of star") {
        glm::vec2 test_position(52, 50);
        REQUIRE(star.DoesStarTouchPoint(test_position));
    }

    SECTION("Vertical Position Difference; touch on edge of star") {
        glm::vec2 test_position(50, 52);
        REQUIRE(star.DoesStarTouchPoint(test_position));
    }

    SECTION("Diagonal Position Difference; touch on interior of star") {
        glm::vec2 test_position(51, 51);
        REQUIRE(star.DoesStarTouchPoint(test_position));
    }
}

TEST_CASE("Update Star Position") {
    SECTION("Negative Slope (from viewing perspective); star heads right and down") {
        // radius of all stars is 2
        ShootingStar star(glm::vec2(50, 50),
                          ci::Color(0, 255, 0), M_PI / 4);
        star.Update();
        REQUIRE(star.GetPosition() == glm::vec2(50 + kMoveByX, 50 + kMoveByX));
    }

    SECTION("Positive Slope (from viewing perspective); star heads left and down") {
        // radius of all stars is 2
        ShootingStar star(glm::vec2(50, 50),
                          ci::Color(0, 255, 0), 3 * M_PI / 4);
        star.Update();
        REQUIRE(star.GetPosition() == glm::vec2(50 - kMoveByX, 50 + kMoveByX));
    }

    SECTION("Negative Slope (from viewing perspective); star heads left and up") {
        // radius of all stars is 2
        ShootingStar star(glm::vec2(50, 50),
                          ci::Color(0, 255, 0), 5 * M_PI / 4);
        star.Update();
        REQUIRE(star.GetPosition() == glm::vec2(50 - kMoveByX, 50 - kMoveByX));
    }

    SECTION("Positive Slope (from viewing perspective); star heads right and up") {
        // radius of all stars is 2
        ShootingStar star(glm::vec2(50, 50),
                          ci::Color(0, 255, 0), 7 * M_PI / 4);
        star.Update();
        REQUIRE(star.GetPosition() == glm::vec2(50 + kMoveByX, 50 + kMoveByX));
    }

    SECTION("Undefined Slope (from viewing perspective); star heads directly down") {
        // radius of all stars is 2
        ShootingStar star(glm::vec2(50, 50),
                          ci::Color(0, 255, 0), 3 * M_PI / 2);
        star.Update();
        REQUIRE(star.GetPosition() == glm::vec2(50, 50 - kMoveByX));
    }

    SECTION("Undefined Slope (from viewing perspective); star heads directly up") {
        // radius of all stars is 2
        ShootingStar star(glm::vec2(50, 50),
                          ci::Color(0, 255, 0), M_PI / 2);
        star.Update();
        REQUIRE(star.GetPosition() == glm::vec2(50, 50 - kMoveByX));
    }
}

TEST_CASE("Star Disappear Progressively") {
    ShootingStar star(glm::vec2(50, 50),
                      ci::Color(0, 255, 0), M_PI / 4);

    star.Update(); // Updates star position and increases past_position_ size by 1
    REQUIRE_FALSE(star.HasDisappeared());

    SECTION("Star Fully Disappears") {
        star.DisappearProgressively(); // 1st position is a past position
        star.DisappearProgressively();
        REQUIRE(star.HasDisappeared());
    }

    SECTION("Update After Star has Disappeared") {
        star.DisappearProgressively(); // 1st position is a past position
        star.Update();
        star.DisappearProgressively();
        REQUIRE(star.HasDisappeared());
    }
}
