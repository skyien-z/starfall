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
    /**
     * Explicit constructor of shooting star
     *
     * @param starting_position; starting center position of head star
     * @param color; ci::Color representing star color
     * @param trajectory_angle of star path
     */
    ShootingStar(const glm::vec2& starting_position, const ci::Color& color,
                 float trajectory_angle);

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
     * @param x_value of point to check for star head contact
     * @param y_value of point to check for star head contact
     * @return true if star head touches point; false otherwise
     */
    bool DoesStarTouchPoint(float x_value, float y_value) const;

    /**
     * Checks if last tail star (the first star in past_positions) has
     * either its x or y value (depending on the passed in boolean) is
     * at the value of passed in float value.
     *
     * @param coordinate_value; float to check position element against
     * @param is_x_coordinate; boolean denoting whether to check the
     * x or y value
     * @return true if position element and coordinate element match,
     * false otherwise
     */
    bool DoesStarTailHaveCoordinateValue(float coordinate_value,
                                         bool is_x_coordinate) const;

    /**
     * Removes star at the last position from past positions list,
     * sets is_disappearing to true, which stops the star from
     * updating its position, drawing its head, or checking its boundaries.
     */
    void DisappearProgressively();

    /**
     * Returns when past_positions_ is empty, which is when the star
     * disappears from view if it has hit a boundary.
     *
     * @return state of past_positions_.empty()
     */
    bool HasDisappeared() const;

    /**
     * Returns when is_disappearing is true, which is when last star
     * that makes up star tail leaves an edge of the canvas (this
     * functionality is handled by the canvas class)
     *
     * @return bool is_disappearing
     */
    bool IsDisappearing() const;

    const glm::vec2& GetPosition() const;

    size_t GetStarRadius() const;

 private:
    static constexpr size_t kMoveByXPixels = 2;
    static constexpr size_t star_radius_ = 2;

    // Star tail length in pixels is
    // (star_radius_/2) * tail_length_proportion_
    static constexpr int tail_length_proportion_ = 15;

    // variables that change as app updates
    glm::vec2 position_;
    bool is_disappearing;

    // variables that are never changed once
    // star is initialized
    ci::ColorA color_;
    float trajectory_angle_;

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
    void DrawStarHead(glm::vec2 star_position) const;

    void DrawStarTail() const;

    /**
     * Changes current position according to y = m x + b; m = tan(y) where
     * y is in radians. Note that cinder graphically flips Q1 with Q4 and
     * Q2 with Q3 (so a trajectory of Pi/4 will update the position to go
     * down and right in the cinder app).
     */
    void UpdatePosition();
};
}