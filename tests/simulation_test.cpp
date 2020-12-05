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
    REQUIRE(test_simulation.GetParagraphLines()[0] == "Another star crossed the sky,");
}