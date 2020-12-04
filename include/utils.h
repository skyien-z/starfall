#pragma once

#include <cinder/Color.h>

namespace starfall {

    /**
     * Generates and returns random float from [lower_bound, upper_bound).
     */
    float GetRandomFloat(float lower_bound, float upper_bound);

    /**
     * Returns a random float [0, Pi/3).
     *
     * A trajectory that is abs(tan(trajectory)) < 2 will guarantee that the
     * change in y of a particle will not exceed the change in x.
     */
    float GetRandomRightAndDownTrajectory();

    /**
     * Returns a random float [2*Pi/3, Pi).
     *
     * A trajectory that is abs(tan(trajectory)) < 2 will guarantee that the
     * change in y of a particle will not exceed the change in x.
     */
    float GetRandomLeftAndDownTrajectory();

    /**
     * Returns a random float [Pi, 4*Pi/3).
     *
     * A trajectory that is abs(tan(trajectory)) < 2 will guarantee that the
     * change in y of a particle will not exceed the change in x.
     */
    float GetRandomLeftAndUpTrajectory();

    /**
     * Returns a random float [5*Pi/3, 2*Pi).
     *
     * A trajectory that is abs(tan(trajectory)) < 2 will guarantee that the
     * change in y of a particle will not exceed the change in x.
     */
    float GetRandomRightAndUpTrajectory();

    /**
     * Generate random color based on randomly chosen rgb values
     * @return color as ColorA
     */
    ci::Color GetRandomColor();

    /**
     * Returns a vec2 of a random starting position within the edges
     * given.
     *
     * @param top_edge; lowest y value
     * @param bottom_edge; highest y value
     * @param left_edge; lowest x value
     * @param right_edge; highest x value
     * @return
     */
    glm::vec2 GetRandomStartingPosition(float top_edge, float bottom_edge,
                                        float left_edge, float right_edge);

}