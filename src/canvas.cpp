#include "canvas.h"

namespace starfall {

Canvas::Canvas(const glm::vec2 &top_left_corner, double canvas_size, double margin) {
//    ShootingStar star(glm::vec2(50, 50),
//                      ci::Color(0, 255, 0), M_PI / 4);
//    star_list_.push_back(star);
}

void Canvas::Draw() const {
    for (const auto &star: star_list_) {
        star.Draw();
    }
}

void Canvas::Update() {
    for (size_t i = 0; i < star_list_.size(); i++) {
        // Shortens star if star touches boundary and deletes star
        // when star is hidden from view
        if (star_list_[i].HasDisappeared()) {
            auto star_to_remove_it = star_list_.begin() + i;
            if (star_to_remove_it != star_list_.end()) {
                star_list_.erase(star_to_remove_it);
            }
            break;
        } else if (IsStarDisappearing(star_list_[i])) {
            star_list_[i].DisappearProgressively();
            break;
        }

        star_list_[i].Update(); // Will not change star position if star touches boundaries
    }
}

void Canvas::AddPointToBoundaries(const glm::vec2 &boundary_point) {
    boundary_points_.push_back(boundary_point);
}

bool Canvas::IsStarDisappearing(const ShootingStar& star) const {
    // Disappeared star will not touch any points
    if (star.HasDisappeared()) {
        return false;
    }

    for (const glm::vec2& boundary_point: boundary_points_) {
        if (star.DoesStarTouchPoint(boundary_point)) {
            return true;
        }
    }

    return false;
}

void Canvas::AddStarToList(const glm::vec2 &starting_position,
                           const cinder::Color &star_color) {

}

void Canvas::AddStarToList(const ShootingStar& star) {
    star_list_.push_back(star);
}

const std::vector<ShootingStar> &Canvas::GetStarList() {
    return star_list_;
}

}