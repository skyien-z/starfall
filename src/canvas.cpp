#include "canvas.h"

namespace starfall {

Canvas::Canvas(const glm::vec2 &top_left_corner, double canvas_size, double margin) {
    ShootingStar star(glm::vec2(50, 50),
                      ci::Color(0, 255, 0), M_PI / 4);
    star_list_.push_back(star);
}

void Canvas::Draw() const {
    for (const auto &star: star_list_) {
        star.Draw();
    }
}

void Canvas::Update() {
    for (auto &star: star_list_) {
        // Shortens star if star touches boundary and deletes star
        // when star is hidden from view
        if (IsStarDisappearing(star)) {
            star.Disappear_Behind_Boundary();
            std::remove_if(star_list_.begin(),
                           star_list_.end(), HasStarDisappeared);
            break;
        }
        star.Update(); // Will not change position if star touches boundaries
    }
}

void Canvas::AddPointToBoundaries(const glm::vec2 &boundary_point) {
    boundary_points_.push_back(boundary_point);
}

bool Canvas::IsStarDisappearing(const ShootingStar& star) const {
    // Disappeared star will not touch any points
    if (HasStarDisappeared(star)) {
        return false;
    }

    for (const glm::vec2& boundary_point: boundary_points_) {
        if (star.DoesStarTouchPoint(boundary_point)) {
            return true;
        }
    }

    return false;
}

void Canvas::AddStarToList(const ShootingStar& star) {
    star_list_.push_back(star);
}

const std::vector<ShootingStar> &Canvas::GetStarList() {
    return star_list_;
}

bool Canvas::HasStarDisappeared(const ShootingStar& star){
    return star.HasDisappeared();
}

}