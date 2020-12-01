#include "shooting_star.h"

namespace starfall {

ShootingStar::ShootingStar(glm::vec2 starting_position, ci::Color color,
float trajectory_angle) : position_(starting_position),
                            color_(color),
                            trajectory_angle_(trajectory_angle) {
    timer.start();
}

void ShootingStar::Update() {
    // Adds first position to past_positions_
    if (past_positions_.empty()) {
        past_positions_.push_back(glm::vec2(position_.x, position_.y));
    }

    UpdatePosition();

    // Adds current position to past_positions_ if current position is at least
    // radius/2 away from last star in past_positions
    if (abs(position_.x - past_positions_.back().x) >= star_head_radius_/2) {
        past_positions_.push_back(glm::vec2(position_.x, position_.y));
    }

    // Keeps the length of the star tail to a constant
    if (past_positions_.size() == tail_length_proportion_) {
        past_positions_.erase(past_positions_.begin());
    }
}

void ShootingStar::Draw() const {
    // Draws "stars" that aggregate into colored star tail
    for (const glm::vec2& past_position: past_positions_) {
        DrawStar(past_position, false);
    }

    // Draws current star head
    DrawStar(position_, true);
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

bool ShootingStar::DoesStarTouchPoint(glm::vec2 &point_on_graph) {
    return length(position_ - point_on_graph) <= star_head_radius_;
}

void ShootingStar::RemoveStarHead() {
    past_positions_.erase(past_positions_.begin());
}

void ShootingStar::UpdatePosition() {
    position_.x = kMoveByXPixels + position_.x;
    position_.y = std::tan(trajectory_angle_) * kMoveByXPixels + position_.y;
}

const glm::vec2 &ShootingStar::GetPosition() const {
    return position_;
}

bool ShootingStar::GetIsHeadStar() {
    return is_head_star_;
}

void ShootingStar::SetIsHeadStar(bool is_head_star) {
    is_head_star_ = is_head_star;
}

}

