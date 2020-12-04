#include "canvas.h"

namespace starfall {

    Canvas::Canvas() {}

    Canvas::Canvas(const glm::vec2 &top_left_corner, size_t canvas_width, size_t canvas_height) {
        top_edge_ = top_left_corner.y;
        bottom_edge_ = top_edge_ + canvas_height;

        left_edge_ = top_left_corner.x;
        right_edge_ = left_edge_ + canvas_width;
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
            }

            star_list_[i].Update(); // Will not change star position if star touches boundaries
        }
    }

    void Canvas::AddPointToBoundaries(const glm::vec2 &boundary_point) {
        //boundary_points_.push_back(boundary_point);

        // if x value key doesn't exist, [] creates key and adds y value to
        // vector of y values. If key exists, just add y value to y value list.
        boundary_points_[boundary_point.x].push_back(boundary_point.y);

    }

    void Canvas::RemoveBoundaries() {
        boundary_points_.clear();
    }

bool Canvas::IsStarDisappearingBehindBoundary(const ShootingStar &star) {
    // variable set to true the first time DisappearProgressively() is called
    if (star.IsDisappearing()) {
        return true;
    }

    // Get the lowest and highest x values of the star head
    int star_lowest_x = star.GetPosition().x - star.GetStarRadius();
    int star_highest_x = star.GetPosition().x + star.GetStarRadius();

    // loops through x values of star head and checks if boundary points
    // with the same x values are within radius of the star head center.
    for (int x_value = star_lowest_x; x_value < star_highest_x + 1; x_value++) {
        if (boundary_points_[x_value].empty()) {
            continue;
        }

        // gets vector of boundary y values with given boundary x value
        std::vector<int> list_of_y_values = boundary_points_[x_value];

        // loop through all points of boundary that have given x value
        // and return true if star touches any boundary point.
        for (int y_value: list_of_y_values) {
            if (star.DoesStarTouchPoint(x_value, y_value)) {
                return true;
            }
        }
    }
    return false;
}


bool Canvas::IsStarOutOfBounds(const ShootingStar &star) const {
    return star.DoesStarTailHaveCoordinateValue(top_edge_, false) ||
           star.DoesStarTailHaveCoordinateValue(bottom_edge_, false) ||
           star.DoesStarTailHaveCoordinateValue(right_edge_, true) ||
           star.DoesStarTailHaveCoordinateValue(left_edge_, true);
}

void Canvas::AddStarToList(const glm::vec2 &starting_position,
                           const cinder::ColorA &star_color, float trajectory) {
    AddStarToList(ShootingStar(starting_position, star_color, trajectory));
}

void Canvas::AddStarToList(const ShootingStar& star) {
    star_list_.push_back(star);
}

const std::vector<ShootingStar> &Canvas::GetStarList() {
    return star_list_;
}

}