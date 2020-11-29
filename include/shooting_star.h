#pragma once
#include "cinder/gl/gl.h"

namespace starfall {
class ShootingStar {
  public:
    ShootingStar(glm::vec2 starting_position, ci::Color color,
                 float trajectory_angle, float star_head_radius);

    /**
     * Renders shooting star and its tail
     */
    void Draw() const;

    /**
     * Updates star's position using y = m x + b where
     * m = tan(y) where y is in radians.
     */
    void UpdatePosition();

  private:
    static constexpr size_t kMoveByXPixels = 1;

    // variables that change with timer
    glm::vec2 position_;

    // variables that are never changed once
    // star is initialized
    ci::Color color_;
    float trajectory_angle_;
    float star_head_radius_;
    ci::Color darker_color_;

    // variables that depend on other variables
    // for initialization
    float star_hue_radius_;
    float tail_length_;

    void DrawTail() const;
};
}