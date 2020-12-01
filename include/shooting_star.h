#pragma once

#include <cinder/Timer.h>
#include "cinder/gl/gl.h"
#include "graphic.h"

namespace starfall {
class ShootingStar: public Graphic {
  public:
    ShootingStar(glm::vec2 starting_position, ci::Color color,
                 float trajectory_angle);

    /**
     * Renders shooting star and its tail.
     */
    void Draw() const;

    /**
     * Updates star's position using y = m x + b where
     * m = tan(y) where y is in radians.
     */
    void Update();

    /**
     * Checks if star head touches point given
     *
     * @param point_on_graph to check for star head contact
     * @return true if star head touches point; false otherwise
     */
    bool DoesStarTouchPoint(glm::vec2& point_on_graph);

    const glm::vec2& GetPosition() const;

    void RemoveFirstStar();

 private:
    static constexpr size_t kMoveByXPixels = 1;
    static constexpr float star_head_radius_ = 2;

    // Star tail length in pixels is
    // (star_head_radius_/2) * tail_length_proportion_
    static constexpr int tail_length_proportion_ = 30;

    // variables that change with timer
    glm::vec2 position_;

    // variables that are never changed once
    // star is initialized
    ci::Color color_;
    float trajectory_angle_;

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
};
}