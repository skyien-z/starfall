#pragma once
#include "cinder/gl/gl.h"
#include "graphic.h"

namespace starfall {
class ShootingStar: public Graphic {
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
    void Update();

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

    // used to draw tail of shooting star
    std::vector<glm::vec2> past_positions_;

    void DrawStarTail() const;

    void DrawStar(glm::vec2 star_position, bool is_head_star) const;
};
}