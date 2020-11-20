#include "shooting_star.h"

ShootingStar::ShootingStar(glm::vec2 starting_position, ci::Color color,
float trajectory_angle, float star_head_radius) : position_(starting_position), color_(color),
trajectory_angle_(trajectory_angle), star_head_radius_(star_head_radius) {
    star_hue_radius_ = star_head_radius_ * 3;
    tail_length_ = star_head_radius_ * 2;

    // gets a darker version of current color
    darker_color_ = color_;
    glm::vec3 darker_hue = static_cast<float>(0.25) * color_.get(ci::CM_RGB);

    darker_color_.set(ci::CM_RGB, darker_hue);
}

void ShootingStar::UpdatePosition() {
    // y = m x + b; m = tan(y) where y is in radians
    position_.x = kMoveByXPixels + position_.x;
    position_.y = std::tan(trajectory_angle_) * kMoveByXPixels + position_.y;
}

void ShootingStar::Draw() const {
    // draws outer "shadow" of star head
    ci::gl::color(ci::Color((darker_color_)));
    ci::gl::drawSolidCircle (position_, star_hue_radius_);

    // draws star tail
    DrawTail();

    // draws star head
    ci::gl::color(ci::Color((color_)));
    ci::gl::drawSolidCircle (position_, star_head_radius_);
}

void ShootingStar::DrawTail() const {
    // draws star tail
    glm::vec2 top_left_corner = position_ - star_head_radius_; // TODO: figure out attachment properly
    glm::vec2 bottom_right_corner = top_left_corner + glm::vec2 (tail_length_, tail_length_);

    ci::gl::pushModelMatrix();
    ci::gl::translate(position_.x, position_.y);
    ci::gl::rotate(trajectory_angle_);

    ci::Rectf tail(top_left_corner, bottom_right_corner);
    ci::gl::drawSolidRoundedRect(tail, 1);

    ci::gl::popModelMatrix();
}

