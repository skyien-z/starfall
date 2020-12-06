#include <random>
#include "utils.h"

namespace starfall {

float GetRandomFloat(float lower_bound, float upper_bound)
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

    std::uniform_real_distribution<> distribution(lower_bound, upper_bound);
    return distribution(gen);
}

int GetRandomInt(int lower_bound, int upper_bound) {
    std::random_device rd;
    std::mt19937 generator(rd());

    // upper_bound + 1 makes the distribution inclusive to the bounds
    std::uniform_int_distribution<> distribution(lower_bound, upper_bound + 1);
    return distribution(generator);
}

float GetRandomRightAndDownTrajectory() {
    return GetRandomFloat(0, M_PI/3);
}

float GetRandomRightTrajectory() {
    return GetRandomFloat(5*M_PI/3, 7*M_PI/3);
}

float GetRandomLeftTrajectory() {
    return GetRandomFloat(2*M_PI/3, 4*M_PI/3);
}

float GetRandomTrajectory() {
    switch (GetRandomInt(1, 2)) {
        case 1:
            return GetRandomRightTrajectory();
        case 2:
            return GetRandomLeftTrajectory();
    }
    return GetRandomLeftTrajectory();
}

ci::Color GetRandomColor() {
    return ci::Color( ci::CM_HSV, GetRandomFloat(0, 1), 1, 1 );
}

glm::vec2 GetRandomStartingPosition(float left_edge, float right_edge,
                                    float bottom_edge, float top_edge) {
    return glm::vec2(GetRandomInt(left_edge, right_edge),
                     GetRandomInt(bottom_edge, top_edge));
}
} // namespace starfall
