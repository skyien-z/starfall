#include "starfall_app.h"

namespace starfall {

StarfallApp::StarfallApp() {
    current_color_ = ci::Color(0, 255, 0);
    current_trajectory_key_ = 1;

    trajectory_selection_ = {
            {0, 0},
            {1, M_PI/4},
            {2, M_PI/2},
            {3, 3*M_PI/4},
            {4, M_PI},
            {5, 5*M_PI/4},
            {6, 3*M_PI/2},
            {7, 7*M_PI/4}
    };
}

void StarfallApp::draw() {
//  ci::gl::clear();
    ci::gl::draw(background_image_);

    canvas_.Draw();
}

void StarfallApp::setup() {
    auto image = ci::loadImage( "/Users/user/CLionProjects/cinder_0.9.2_mac/my_projects/"
                                "final-project-skyien-z/resources/mountains_for_starfall.png" );
    background_image_ = ci::gl::Texture2d::create(image);
    setWindowSize(background_image_->getWidth(),
                  background_image_->getHeight());

    // Conform canvas size to image specifications
    Canvas this_canvas(glm::vec2(0, 0), getWindowWidth(),getWindowHeight());
    canvas_ = this_canvas;
}

void StarfallApp::update() {
    canvas_.Update();
}

void StarfallApp::mouseDown(ci::app::MouseEvent event) {
    if (event.isRightDown()) {
        canvas_.AddStarToList(event.getPos(), current_color_,
                              trajectory_selection_[current_trajectory_key_]);
    }
}

void StarfallApp::mouseDrag(ci::app::MouseEvent event) {
    if (event.isShiftDown()) {
        canvas_.AddPointToBoundaries(event.getPos());
    }
}

void StarfallApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
  case ci::app::KeyEvent::KEY_r:
      current_color_ = ci::ColorA(255, 0, 0, 1);
      break;
  case ci::app::KeyEvent::KEY_g:
      current_color_ = ci::ColorA(0, 255, 0, 1);
      break;
  case ci::app::KeyEvent::KEY_b:
      current_color_ = ci::ColorA(0, 0, 255, 1);
      break;
  case ci::app::KeyEvent::KEY_o:
      current_color_ = ci::ColorA(255, 128, 0, 1);
      break;
  case ci::app::KeyEvent::KEY_TAB:
    canvas_.RemoveBoundaries();
    break;
  case ci::app::KeyEvent::KEY_RIGHT:
      // Goes counterclockwise around the canvas
      (current_trajectory_key_ == 0) ? current_trajectory_key_ = 7 : current_trajectory_key_--;
      break;
  case ci::app::KeyEvent::KEY_LEFT:
      // Goes clockwise around the canvas
      (current_trajectory_key_ == 7) ? current_trajectory_key_ = 0 : current_trajectory_key_++;
      break;
  }

}

}  // namespace ideal_gas
