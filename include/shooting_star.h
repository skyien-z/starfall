#pragma once

#include <cinder/Timer.h>
#include "cinder/gl/gl.h"
#include "graphic.h"

namespace starfall {

/**
 * Creates and renders a single shooting star with its functionality
 */
class ShootingStar: public Graphic {
  public:
    ShootingStar(const glm::vec2& starting_position, const ci::Color& color,
                 float trajectory_angle);

    ShootingStar(const glm::vec2& starting_position, const ci::Color& color);

    ShootingStar(const glm::vec2& starting_position);

    /**
     * Renders shooting star and its tail.
     */
    void Draw() const;

    /**
     * Updates star head's position and position of colored stars
     * that make up the shooting star's tail. Keeps tail length
     * constant.
     */
    void Update();

    /**
     * Checks if star head touches point given.
     *
     * @param point_on_graph to check for star head contact
     * @return true if star head touches point; false otherwise
     */
    bool DoesStarTouchPoint(const glm::vec2& point_on_graph) const;

    /**
     * Checks if last tail star (the first star in past_positions) has
     * either its x or y value (depending on the passed in boolean) is
     * at the value of passed in float value.
     *
     * @param coordinate_value; float to check position element against
     * @param is_x_coordinate; boolean denoting whether to check the x or y value
     * @return true if position element and coordinate element match, false otherwise
     */
    bool DoesStarTailHaveCoordinateValue(float coordinate_value,
                                         bool is_x_coordinate) const;

    const glm::vec2& GetPosition() const;

    /**
     * Removes star at the last position from past positions list,
     * sets is_disappearing to true, which stops the star from
     * updating its position, drawing, its head, or checking its boundaries.
     */
    void DisappearProgressively();

    /**
     * Returns when past_positions_ is empty, which is when the star
     * disappears from view
     *
     * @return state of past_positions_
     */
    bool HasDisappeared() const;

 private:
    static constexpr size_t kMoveByXPixels = 2;
    static constexpr float star_head_radius_ = 2;

    static constexpr float kDefaultTrajectory = M_PI/4;

    // Star tail length in pixels is
    // (star_head_radius_/2) * tail_length_proportion_
    static constexpr int tail_length_proportion_ = 15;

    // variables that change with timer
    glm::vec2 position_;

    // variables that are never changed once
    // star is initialized
    ci::Color color_;
    float trajectory_angle_;
    bool is_disappearing;

    ci::Timer timer;
    // past positions of star used to draw tail of shooting star
    std::vector<glm::vec2> past_positions_;

    /**
     * Draws single circle representing a star. The head star will be
     * rendered in white, while the tail will be rendered in the star's
     * initialized color.
     *
     * @param star_position pixel position representing where to draw star.
     * @param is_head_star; true if star to be rendered is the "head" star
     */
    void DrawStar(glm::vec2 star_position, bool is_head_star) const;

    /**
     * Changes current position according to y = m x + b; m = tan(y) where y is in radians
     */
    void UpdatePosition();

    void Initialize_Variables(const glm::vec2& starting_position);
};
}