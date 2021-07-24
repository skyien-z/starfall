#include <catch2/catch.hpp>
#include <vector>
#include "cinder/gl/gl.h"
#include "simulation.h"

using namespace starfall;

TEST_CASE("Reading in Starfall Paragraph") {
    Canvas test_canvas(glm::vec2(50, 50),
                       200, 200);
    Simulation test_simulation (test_canvas);

    REQUIRE(test_simulation.GetParagraphLines().size() == 25);
    REQUIRE(test_simulation.GetParagraphLines()[0] ==
    "Another star crossed the sky,");
}

// All other testable functionality of the simulation is tested elsewhere.
// Each component of a generating a star in bounds has been tested in
// utils_test.cpp or canvas_test.cpp. The only non-trivial not unit-tested
// logic of this class lies in updating the simulation, but as Update() only
// changes state based on a timer, it cannot be unit-tested. So, to account
// for this, I played the simulation through the cinder app and checked with
// a timer that all Update() and Draw() functionality works as expected.