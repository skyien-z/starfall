#include "shooting_star.h"

namespace starfall {

ShootingStar::ShootingStar(glm::vec2 starting_position, ci::Color color,
float trajectory_angle, float star_head_radius) : position_(starting_position),
                            color_(color),
                            trajectory_angle_(trajectory_angle),
                            star_head_radius_(star_head_radius) {
    star_hue_radius_ = star_head_radius_ * 2;
    tail_length_ = star_head_radius_ * 2;

    // gets a darker version of current color
    glm::vec3 darker_hue = static_cast<float>(0.25) * color_.get(ci::CM_RGB);

    darker_color_.set(ci::CM_RGB, darker_hue);
}

void ShootingStar::UpdatePosition() {
    // Adds current position to past_positions_
    if (past_positions_.empty()) {
        past_positions_.push_back(glm::vec2(position_.x, position_.y));
    }

    // Changes current position according to y = m x + b; m = tan(y) where y is in radians
    position_.x = kMoveByXPixels + position_.x;
    position_.y = std::tan(trajectory_angle_) * kMoveByXPixels + position_.y;

    if (abs(position_.x - past_positions_.back().x) >= star_hue_radius_/2) {
        past_positions_.push_back(glm::vec2(position_.x, position_.y));
    }
}

void ShootingStar::Draw() const {
    // Draws "stars" that aggregate into star tail
    DrawTail();

    // Draws current star head
    DrawStar(position_, true);
}

void ShootingStar::DrawTail() const {
    // Draws "stars" that aggregate into star tail
    for (const glm::vec2& past_position: past_positions_) {
        DrawStar(past_position, false);
    }
}

void ShootingStar::DrawStar(glm::vec2 star_position, bool is_head_star) const {
    // draws tail star
    ci::gl::ScopedColor scpColor(color_);
    ci::gl::drawSolidCircle(star_position, star_hue_radius_);

    // draws white star head
    if (is_head_star) {
        ci::gl::color(ci::ColorA( 255, 255, 255));
        ci::gl::drawSolidCircle(star_position, star_hue_radius_);
    }
}

}

