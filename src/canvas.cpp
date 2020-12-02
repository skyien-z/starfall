#include "canvas.h"

namespace starfall {

Canvas::Canvas() {}

Canvas::Canvas(const glm::vec2 &top_left_corner, size_t canvas_width, size_t canvas_height) {
    top_bound_ = top_left_corner.y;
    bottom_bound_ = top_bound_ + canvas_height;

    left_bound_ = top_left_corner.x;
    right_bound_ = left_bound_ + canvas_width;
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
        if (star_list_[i].HasDisappeared() || IsStarOutOfBounds(star_list_[i])) {
            auto star_to_remove_it = star_list_.begin() + i;
            if (star_to_remove_it != star_list_.end()) {
                star_list_.erase(star_to_remove_it);
                break;
            }
        } else if (IsStarDisappearingBehindBoundary(star_list_[i])) {
            star_list_[i].DisappearProgressively();
            break;
        }

        star_list_[i].Update(); // Will not change star position if star touches boundaries
    }
}

void Canvas::AddPointToBoundaries(const glm::vec2 &boundary_point) {
    boundary_points_.push_back(boundary_point);
}

void Canvas::RemoveBoundaries() {
    boundary_points_.clear();
}

bool Canvas::IsStarDisappearingBehindBoundary(const ShootingStar& star) const {
    for (const glm::vec2& boundary_point: boundary_points_) {
        if (star.DoesStarTouchPoint(boundary_point)) {
            return true;
        }
    }

    return false;
}

bool Canvas::IsStarOutOfBounds(const ShootingStar &star) const {
    return star.DoesStarTailHaveCoordinateValue(top_bound_, false) ||
            star.DoesStarTailHaveCoordinateValue(bottom_bound_, false) ||
            star.DoesStarTailHaveCoordinateValue(right_bound_, true) ||
            star.DoesStarTailHaveCoordinateValue(left_bound_, true);
}

void Canvas::AddStarToList(const glm::vec2 &starting_position) {
    AddStarToList(ShootingStar(starting_position));
}

void Canvas::AddStarToList(const glm::vec2 &starting_position,
                           const cinder::Color &star_color, float trajectory) {
    AddStarToList(ShootingStar(starting_position, star_color, trajectory));
}

void Canvas::AddStarToList(const ShootingStar& star) {
    star_list_.push_back(star);
}

const std::vector<ShootingStar> &Canvas::GetStarList() {
    return star_list_;
}

}