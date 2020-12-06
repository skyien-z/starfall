#pragma once

#include <cinder/Color.h>

namespace starfall {

    /**
     * Generates and returns random float from [lower_bound, upper_bound).
     */
    float GetRandomFloat(float lower_bound, float upper_bound);

    /**
     * Generates and returns random int from [lower_bound, upper_bound].
     */
    int GetRandomInt(int lower_bound, int upper_bound);

    /**
     * Returns a random float [2*Pi/3, 4*Pi/3) U [5*Pi/3, 7*Pi/3).
     *
     * A trajectory that is abs(tan(trajectory)) < 2 will guarantee that
     * the change in y of a particle will not exceed the change in x.
     */
    float GetRandomTrajectory();

    /**
     * Generate random color based on randomly chosen rgb values
     * @return color as ColorA
     */
    ci::Color GetRandomColor();

    /**
     * Returns a vec2 of a random starting position within the edges
     * given.
     *
     * @param left_edge; lowest x value
     * @param right_edge; highest x value
     * @param bottom_edge; lowest y value
     * @param top_edge; highest y value
     *
     * @return random starting position within edge bounds
     */
    glm::vec2 GetRandomStartingPosition(float left_edge, float right_edge,
                                        float bottom_edge, float top_edge);

} // namespace starfall