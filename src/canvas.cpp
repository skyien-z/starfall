#include "canvas.h"

namespace starfall {

Canvas::Canvas(const glm::vec2 &top_left_corner, double canvas_size, double margin) {
    ShootingStar star(glm::vec2(50, 50),
                      ci::Color(0, 255, 0), M_PI / 4);
    star_list_.push_back(star);
}

void Canvas::Draw() const {
    //background_.Draw();

    for (auto &star: star_list_) {
        star.Draw();
    }
}

void Canvas::Update() {
    for (auto &star: star_list_) {
        star.Update();
    }
}

void Canvas::AddPointToBoundaries(const glm::vec2 &boundary_point) {
    boundary_points_.push_back(boundary_point);
}

}