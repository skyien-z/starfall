#include <catch2/catch.hpp>
#include <vector>
#include "cinder/gl/gl.h"
#include "canvas.h"

using namespace ideal_gas;

TEST_CASE("React to Vertical (y-axis) Wall") {
    double initial_velocity = 0.15;
    glm::vec2 top_left_corner (50, 50);
    Canvas test_canvas (top_left_corner, 20, 5);

    SECTION("Right Wall") {
        glm::vec2 test_position (50, 60);
        Particle test_particle (test_position,1, 1, "black");

        test_canvas.AddParticle(test_particle);
        test_canvas.Update();

        REQUIRE(test_canvas.GetParticleList()[0].GetVelocity() ==
                glm::vec2 (-initial_velocity, initial_velocity));

        REQUIRE(test_canvas.GetParticleList()[0].GetPosition() ==
                glm::vec2 (50 - initial_velocity, 60 + initial_velocity));
    }

    SECTION("Left Wall") {
        glm::vec2 test_position (70, 60);
        Particle test_particle (test_position,1, 1, "black");

        test_canvas.AddParticle(test_particle);
        test_canvas.Update();

        REQUIRE(test_canvas.GetParticleList()[0].GetVelocity() ==
                glm::vec2 (-initial_velocity, initial_velocity));

        REQUIRE(test_canvas.GetParticleList()[0].GetPosition() ==
                glm::vec2 (70 - initial_velocity, 60 + initial_velocity));
    }
}

TEST_CASE("React to Horizontal Wall (x axis)") {
    double initial_velocity = 0.15;
    glm::vec2 top_left_corner(50, 50);
    Canvas test_canvas(top_left_corner, 20, 5);

    SECTION("Top Wall") {
        glm::vec2 test_position (60, 50);
        Particle test_particle (test_position,1, 1, "black");

        test_canvas.AddParticle(test_particle);
        test_canvas.Update();

        REQUIRE(test_canvas.GetParticleList()[0].GetVelocity() ==
                glm::vec2 (initial_velocity, -initial_velocity));

        REQUIRE(test_canvas.GetParticleList()[0].GetPosition() ==
                glm::vec2 (60 + initial_velocity, 50 - initial_velocity));
    }

    SECTION("Bottom Wall") {
        glm::vec2 test_position (60, 75); // y = 75 is location of bottom wall
        Particle test_particle (test_position,1, 1, "black");

        test_canvas.AddParticle(test_particle);
        test_canvas.Update();

        REQUIRE(test_canvas.GetParticleList()[0].GetVelocity() ==
                glm::vec2 (initial_velocity, -initial_velocity));

        REQUIRE(test_canvas.GetParticleList()[0].GetPosition() ==
                glm::vec2 (60 + initial_velocity, 75 - initial_velocity));
    }
}

TEST_CASE("Test Adding a Custom Particle to a Random Position") {
    glm::vec2 top_left_corner(50, 50);
    Canvas test_canvas(top_left_corner, 20, 5);

    for (size_t i = 0; i < 5; i++) {
        test_canvas.AddRandomPositionParticle(4, 2, "black");
    }

    for (size_t i = 0; i < 5; i++) {
        glm::vec2 temp_position = test_canvas.GetParticleList()[i].GetPosition();

        REQUIRE(temp_position.x >= 54.0f);
        REQUIRE(temp_position.x <= 66.0f);
        REQUIRE(temp_position.y >= 54.0f);
        REQUIRE(temp_position.x <= 71.0f);
    }
}

TEST_CASE("Test Scaling Velocities") {
    // Velocity is 0.15 times radius, which is 1
    double initial_velocity = 0.15;

    glm::vec2 top_left_corner(50, 50);
    Canvas test_canvas(top_left_corner, 20, 5);

    for (size_t i = 0; i < 5; i++) {
        test_canvas.AddRandomPositionParticle(1, 2, "black");
    }

    test_canvas.ScaleVelocity(2);

    for (size_t i = 0; i < 5; i++) {
        glm::vec2 temp_velocity = test_canvas.GetParticleList()[i].GetVelocity();
        REQUIRE(temp_velocity.x == (float) initial_velocity * 2);
        REQUIRE(temp_velocity.y == (float) initial_velocity * 2);
    }
}

TEST_CASE("Test Update Graph Speeds") {
    // Velocity is 0.15 times radius, which is 1
    double initial_velocity = 0.15;

    glm::vec2 top_left_corner(50, 50);
    Canvas test_canvas(top_left_corner, 20, 5);

    SECTION("Updating Speed of 1 particle") {
        glm::vec2 test_position(60, 60);
        Particle test_particle(test_position, 1, 1, "black");
        test_canvas.AddParticle(test_particle);

        test_canvas.Update();

        REQUIRE(test_canvas.GetGraphList()[0].GetParticleSpeeds()[0] ==
                glm::length(glm::vec2(initial_velocity, initial_velocity)));
    }

    SECTION("Updating Two Different Particles With The Same Masses") {
        glm::vec2 test_position(60, 60);
        Particle test_particle(test_position, 1, 1, "black");
        test_canvas.AddParticle(test_particle);

        glm::vec2 test_position_2(58, 62);
        Particle test_particle_2(test_position, 1, 1, "blue");
        test_canvas.AddParticle(test_particle);

        test_canvas.Update();

        REQUIRE(test_canvas.GetGraphList()[0].GetParticleSpeeds()[0] ==
                glm::length(glm::vec2(initial_velocity, initial_velocity)));
        REQUIRE(test_canvas.GetGraphList()[0].GetParticleSpeeds()[1] ==
                glm::length(glm::vec2(initial_velocity, initial_velocity)));
    }

    SECTION("Updating Two Different Particles With Different Masses") {
        double new_velocity = 0.15 * 2;

        glm::vec2 test_position(60, 60);
        Particle test_particle(test_position, 1, 1, "black");
        test_canvas.AddParticle(test_particle);

        glm::vec2 test_position_2(58, 62);
        Particle test_particle_2(test_position, 2, 2, "blue");
        test_canvas.AddParticle(test_particle_2);

        test_canvas.Update();

        REQUIRE(test_canvas.GetGraphList()[0].GetParticleSpeeds()[0] ==
                glm::length(glm::vec2(initial_velocity, initial_velocity)));
        REQUIRE(test_canvas.GetGraphList()[1].GetParticleSpeeds()[0] ==
                glm::length(glm::vec2(new_velocity, new_velocity)));
    }

    SECTION("Updating Two Different Particles With Different Masses Twice") {
        double new_velocity = 0.15 * 2;

        glm::vec2 test_position (60, 60);
        Particle test_particle (test_position,1, 1, "black");
        test_canvas.AddParticle(test_particle);

        glm::vec2 test_position_2 (58, 62);
        Particle test_particle_2 (test_position,2, 2, "blue");
        test_canvas.AddParticle(test_particle_2);

        test_canvas.Update();
        test_canvas.Update();

        REQUIRE(test_canvas.GetGraphList()[0].GetParticleSpeeds()[0] ==
                glm::length(glm::vec2 (initial_velocity, initial_velocity)));
        REQUIRE(test_canvas.GetGraphList()[0].GetParticleSpeeds().size() == 1);

        REQUIRE(test_canvas.GetGraphList()[1].GetParticleSpeeds()[0] ==
                glm::length(glm::vec2 (new_velocity, new_velocity)));
        REQUIRE(test_canvas.GetGraphList()[1].GetParticleSpeeds().size() == 1);
    }
}