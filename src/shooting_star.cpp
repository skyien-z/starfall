#include "shooting_star.h"

namespace starfall {

ShootingStar::ShootingStar(const glm::vec2& starting_position,
                           const ci::Color& color,
                           float trajectory_angle) :
                           position_(starting_position),
                           color_(color),
                           trajectory_angle_(trajectory_angle) {
    Initialize_Variables(starting_position);
}

void ShootingStar::Initialize_Variables(const glm::vec2& starting_position) {
    timer.start();

    // Each star only shoots once so adds first position to past_positions_
    past_positions_.push_back(starting_position);
    is_disappearing = false;
}

void ShootingStar::Update() {
    // past_positions_ will only be empty if star is not needed anymore
    if (is_disappearing) {
        return;
    }

    UpdatePosition();

    // Adds current position to past_positions_ if current position is at least
    // radius/2 away from last star in past_positions
    if (length(position_ - past_positions_.back()) >= star_head_radius_/2) {
        past_positions_.push_back(glm::vec2(position_.x, position_.y));
    }

    // Keeps the length of the star tail to a constant
    if (past_positions_.size() == tail_length_proportion_) {
        past_positions_.erase(past_positions_.begin());
    }
}

void ShootingStar::UpdatePosition() {
    // As cinder graphically flips Q1 and Q2 with Q3 and Q4, decreases
    // x position when trajectory is between -Pi/2 and -3 Pi/2
    if (trajectory_angle_ > M_PI/2 && trajectory_angle_ < 3 * M_PI/2) {
        position_.x = position_.x - kMoveByXPixels;
        position_.y = position_.y - std::tan(trajectory_angle_) * kMoveByXPixels;
    } else if (trajectory_angle_ - M_PI/2 < 0.0001) { // tan(Pi/2) is undefined
        // x position remains the same
        position_.y = position_.y -  kMoveByXPixels;
    } else if (trajectory_angle_ - 3*M_PI/2 < 0.0001) { // tan(3 Pi/2) is undefined
        // x position remains the same
        position_.y = position_.y +  kMoveByXPixels;
    } else {
        position_.x = kMoveByXPixels + position_.x;
        position_.y = std::tan(trajectory_angle_) * kMoveByXPixels + position_.y;
    }
}

void ShootingStar::Draw() const {
    // Draws "stars" that aggregate into colored star tail
    for (const glm::vec2& past_position: past_positions_) {
        DrawStar(past_position, false);
    }

    // Draws current star head if star is above mountains
    if (!is_disappearing) {
        DrawStar(position_, true);
    }
}

void ShootingStar::DrawStar(glm::vec2 star_position, bool is_head_star) const {
    // draws tail star
    ci::gl::ScopedColor scpColor(color_);
    ci::gl::drawSolidCircle(star_position, star_head_radius_);

    // draws white star head
    if (is_head_star) {
        ci::gl::color(ci::ColorA( 255, 255, 255));
        ci::gl::drawSolidCircle(star_position, star_head_radius_);
    }
}

bool ShootingStar::DoesStarTouchPoint(const glm::vec2 &point_on_graph) const {
    return length(position_ - point_on_graph) <= star_head_radius_;
}

bool ShootingStar::DoesStarTailHaveCoordinateValue(float coordinate_value,
                                                   bool is_x_coordinate) const {
    return (is_x_coordinate && abs(past_positions_.front().x - coordinate_value) <= star_head_radius_) ||
           (!is_x_coordinate && abs(past_positions_.front().y - coordinate_value) <= star_head_radius_);
}

void ShootingStar::DisappearProgressively() {
    is_disappearing = true;
    past_positions_.erase(past_positions_.begin());
}

const glm::vec2 &ShootingStar::GetPosition() const {
    return position_;
}

bool ShootingStar::HasDisappeared() const{
    return past_positions_.empty();
}

}

