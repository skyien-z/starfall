#include "shooting_star.h"

namespace starfall {

ShootingStar::ShootingStar(const glm::vec2& starting_position,
                           const ci::Color& color,
                           float trajectory_angle) :
                           position_(starting_position),
                           color_(color),
                           trajectory_angle_(trajectory_angle) {

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
    if (length(position_ - past_positions_.back()) >= kStarRadius_ / 2) {
        past_positions_.push_back(glm::vec2(position_.x, position_.y));
    }

    // Keeps the length of the star tail to a constant
    if (past_positions_.size() == kTailLengthProportion_) {
        past_positions_.erase(past_positions_.begin());
    }
}

void ShootingStar::UpdatePosition() {
    // As cinder graphically flips Q1 and Q2 with Q3 and Q4, decreases
    // x position when trajectory is between Pi/2 and 3 Pi/2

    // tan(Pi/2) and tan(3 Pi/2) are undefined, so cases handle them
    if (abs(trajectory_angle_ - M_PI/2) < 0.0001) {
        // x position remains the same
        position_.y = position_.y +  kMoveByXPixels;
    } else if (abs(trajectory_angle_ - 3*M_PI/2) < 0.0001) {
        // x position remains the same
        position_.y = position_.y - kMoveByXPixels;
    } else if (trajectory_angle_ > M_PI/2 && trajectory_angle_ < 3 * M_PI/2) {
        position_.x = position_.x - kMoveByXPixels;
        position_.y = position_.y - std::tan(trajectory_angle_) * kMoveByXPixels;
    } else {
        position_.x = kMoveByXPixels + position_.x;
        position_.y = std::tan(trajectory_angle_) * kMoveByXPixels + position_.y;
    }
}

void ShootingStar::Draw() const {
    DrawStarTail();

    // Draws current star head if star is above mountains
    if (!is_disappearing) {
        DrawStarHead(position_);
    }
}

void ShootingStar::DrawStarHead(glm::vec2 star_position) const {
    // draws white star head
    ci::gl::ScopedColor scpColor(255, 255, 255);
    ci::gl::drawSolidCircle(star_position, kStarRadius_);
}

void ShootingStar::DrawStarTail() const {
    // last star representing tail has alpha of kLastTailStarAlpha
    float color_alpha = kLastTailStarAlpha;

    // size of past_positions_ vector is kTailLengthProportion
    // alpha is incremented so that tail vector closet to star head is 1
    float alpha_increment_by = (1 - color_alpha)/kTailLengthProportion_;

    for (const glm::vec2& past_position: past_positions_) {
        ci::gl::ScopedColor scpColor(color_.r, color_.g, color_.b, color_alpha);
        ci::gl::drawSolidCircle(past_position, kStarRadius_);
        color_alpha += alpha_increment_by;
    }
}

bool ShootingStar::DoesStarTouchPoint(float x_value, float y_value) const {
    // distance will always be positive
    float distance_between_points = sqrt(pow(position_.x - x_value, 2) +
                                         pow(position_.y - y_value, 2));

    return distance_between_points <= kStarRadius_;
}

bool ShootingStar::DoesStarTailHaveCoordinateValue(float coordinate_value,
                                                   bool is_x_coordinate) const {
    // Position of the last "star" that makes up the star tail
    glm::vec2 star_tail_position = past_positions_.front();

    if (is_x_coordinate) {
        return abs(star_tail_position.x - coordinate_value) <= kStarRadius_;
    } else {
        return abs(star_tail_position.y - coordinate_value) <= kStarRadius_;
    }
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

bool ShootingStar::IsDisappearing() const {
    return is_disappearing;
}

}

