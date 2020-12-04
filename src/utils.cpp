#include <random>
#include "utils.h"

namespace starfall {

    float GetRandomFloat(float lower_bound, float upper_bound)
    {
        static std::default_random_engine random_engine;
        static std::uniform_real_distribution<> distribution(lower_bound, upper_bound);
        return distribution(random_engine);
    }

    int GetRandomInt(int lower_bound, int upper_bound) {
        static std::default_random_engine random_engine;

        // upper_bound + 1 makes the distribution inclusive to the bounds
        static std::uniform_int_distribution<> distribution(lower_bound, upper_bound + 1);
        return distribution(random_engine);
    }

    float GetRandomRightAndDownTrajectory() {
        return GetRandomFloat(0, M_PI/3);
    }

    float GetRandomLeftAndDownTrajectory() {
        return GetRandomFloat(2*M_PI/3, M_PI);
    }

    float GetRandomRightAndUpTrajectory() {
        return GetRandomFloat(M_PI, 4*M_PI/3);
    }

    float GetRandomLeftAndUpTrajectory() {
        return GetRandomFloat(5*M_PI/3, 2*M_PI);
    }

    ci::Color GetRandomColor() {
        return ci::Color(GetRandomInt(0, 255),
                         GetRandomInt(0, 255),
                         GetRandomInt(0, 255));
    }

    glm::vec2 GetRandomStartingPosition(float left_edge, float right_edge,
                                        float bottom_edge, float top_edge) {
        return glm::vec2(GetRandomInt(left_edge, right_edge),
                         GetRandomInt(bottom_edge, top_edge));
    }
}
