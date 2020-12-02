#include "starfall_app.h"

namespace starfall {

StarfallApp::StarfallApp() {
    current_color_ = ci::Color(0, 255, 0);
    current_trajectory_ = M_PI / 4;
}

void StarfallApp::draw() {
//  ci::gl::clear();
    ci::gl::draw(background_image_);

    canvas_.Draw();
}

void StarfallApp::setup() {
    auto image = ci::loadImage( "/Users/user/CLionProjects/cinder_0.9.2_mac/my_projects/"
                                "final-project-skyien-z/images/smaller_mountains.png" );
    background_image_ = ci::gl::Texture2d::create(image);
    setWindowSize(background_image_->getWidth(), background_image_->getHeight());

    // Conform canvas size to image specifications
    Canvas this_canvas(getWindowPos(), getWindowWidth(), getWindowHeight());
    canvas_ = this_canvas;
}

void StarfallApp::update() {
    canvas_.Update();
}

void StarfallApp::mouseDown(ci::app::MouseEvent event) {
    if (event.isRightDown()) {
        canvas_.AddStarToList(event.getPos(), current_color_, current_trajectory_);
    }
}

void StarfallApp::mouseDrag(ci::app::MouseEvent event) {
    if (event.isShiftDown()) {
        canvas_.AddPointToBoundaries(event.getPos());
    }
}

void StarfallApp::mouseWheel(ci::app::MouseEvent event) {
    // each wheel increment up increases trajectory by Pi/6
    // while each wheel increment down decreases trajectory by Pi/6
    current_trajectory_ = event.getWheelIncrement() + M_PI/6;
}

void StarfallApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
  case ci::app::KeyEvent::KEY_r:
      current_color_ = ci::Color(255, 0, 0);
      break;
  case ci::app::KeyEvent::KEY_g:
      current_color_ = ci::Color(0, 255, 0);
      break;
  case ci::app::KeyEvent::KEY_b:
      current_color_ = ci::Color(0, 0, 255);
      break;
  case ci::app::KeyEvent::KEY_o:
      current_color_ = ci::Color(255, 128, 0);
      break;
    case ci::app::KeyEvent::KEY_DELETE:
        canvas_.RemoveBoundaries();
      break;
  }
}

}  // namespace ideal_gas
