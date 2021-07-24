#include "canvas.h"

namespace starfall {

Canvas::Canvas(const glm::vec2 &top_left_corner, size_t canvas_width, size_t canvas_height) {
    bottom_edge_ = top_left_corner.y;
    top_edge_ = top_edge_ + canvas_height;

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
        if (star_list_[i].HasDisappeared() ||
        IsStarOutOfBounds(star_list_[i])) {
            auto star_to_remove_it = star_list_.begin() + i;
            if (star_to_remove_it != star_list_.end()) {
                star_list_.erase(star_to_remove_it);
                continue;
            }
        } else if (IsStarDisappearingBehindBoundary(star_list_[i])) {
            star_list_[i].DisappearProgressively();
        }
        // Will not change star position if star touches boundaries
        star_list_[i].Update();
    }
}

void Canvas::AddPointToBoundaries(const glm::vec2 &boundary_point) {
    // if x value key doesn't exist, [] creates key and adds y value to
    // vector of y values. If key exists, just add y value to y value list.
    boundary_points_[boundary_point.x].push_back(boundary_point.y);

}

void Canvas::RemoveBoundaries() {
    boundary_points_.clear();
}

bool Canvas::IsStarDisappearingBehindBoundary(const ShootingStar &star) {
    // if condition is true the first time DisappearProgressively() is called
    if (star.IsDisappearing()) {
        return true;
    }
    // Get the lowest and highest x values of the star head
    int star_lowest_x = star.GetPosition().x - kStarRadius_;
    int star_highest_x = star.GetPosition().x + kStarRadius_;

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
    return star.DoesStarTailHaveCoordinateValue(bottom_edge_, false) ||
           star.DoesStarTailHaveCoordinateValue(top_edge_, false) ||
           star.DoesStarTailHaveCoordinateValue(right_edge_, true) ||
           star.DoesStarTailHaveCoordinateValue(left_edge_, true);
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

void Canvas::ExportBoundaryPointsToFile(const std::string &abs_file_path) {
    std::ofstream output_stream(abs_file_path);
    for (const auto& coordinate : boundary_points_) {
        // coordinate.first is x value; coordinate.second is y value list
        output_stream << coordinate.first << " ";
        for (size_t i = 0; i < coordinate.second.size(); i++) {
            output_stream << coordinate.second[i];
            // Ensures that line doesn't end with a space
            if (i != coordinate.second.size() - 1) {
                output_stream << " ";
            }
        }
        output_stream << "\n";
    }
    output_stream.close();
}

void Canvas::ImportBoundaryPointsFromFile(
        const std::string &abs_file_path) {
    std::ifstream text_stream (abs_file_path);

    std::string line;
    while (!text_stream.eof()) {
        std::getline(text_stream, line);
        std::stringstream one_line_stream(line);

        int x_value;
        // first value of each line is x value key
        one_line_stream >> x_value;

        int y_value;
        std::vector<int> list_of_y_values;
        while (!one_line_stream.eof()) {
            one_line_stream >> y_value;
            list_of_y_values.push_back(y_value);
        }
        boundary_points_.emplace(x_value, list_of_y_values);
    }
    text_stream.close();
}

float Canvas::GetBottomEdge() const {
    return bottom_edge_;
}

float Canvas::GetRightEdge() const {
    return right_edge_;
}

float Canvas::GetLeftEdge() const {
    return left_edge_;
}

const MapXToYList &Canvas::GetBoundaryPoints() const {
    return boundary_points_;
}

} // namespace starfall