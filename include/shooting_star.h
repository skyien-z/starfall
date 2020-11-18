#pragma once
#include "cinder/gl/gl.h"

class ShootingStar {
  public:
    ShootingStar(ci::Color color, glm::vec2 starting_position);

    /**
     * Renders shooting star and its tail
     */
    void Draw() const;

    /**
     * Updates star's position.
     */
    void UpdatePosition();

  private:
    // variables that change with timer
    glm::vec2 position_;
    glm::vec2 velocity_;

    // variables that are never changed once
    // star is initialized
    ci::Color color_;
    double trajectory_angle_;
    size_t star_head_radius_;

    // variables that depend on other variables
    // for initialization
    size_t star_hue_radius_;
    size_t tail_length_;
};