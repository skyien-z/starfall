#pragma once
#include "cinder/gl/gl.h"
#include "shooting_star.h"

class Canvas {
  public:
    Canvas(const glm::vec2& top_left_corner, double canvas_size, double margin);

    void Draw() const;

    void Update();

private:
    std::vector<ShootingStar> star_list_;
};
