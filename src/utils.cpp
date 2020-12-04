#include <random>
#include "utils.h"

namespace starfall {

    float GetRandomFloat(float lower_bound, float upper_bound)
    {
        static std::default_random_engine random_engine;
        static std::uniform_real_distribution<> distribution(lower_bound, lower_bound);
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

    }

    glm::vec2 GetRandomStartingPosition(float top_edge, float bottom_edge,
                                        float left_edge, float right_edge) {

    }
}
