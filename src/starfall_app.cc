#include "starfall_app.h"

namespace starfall {

StarfallApp::StarfallApp(): canvas_(glm::vec2(kMargin, kMargin),
              kWindowSize, kMargin) {
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
    setWindowSize(background_image_->getWidth(), background_image_->getHeight() );
}

void StarfallApp::update() {
    canvas_.Update();
}

void StarfallApp::mouseDown(ci::app::MouseEvent event) {
    if (event.isLeftDown()) {
        canvas_.AddPointToBoundaries(event.getPos());
    }
}


void StarfallApp::mouseDrag(ci::app::MouseEvent event) {
    if (event.isShiftDown()) {
        canvas_.AddPointToBoundaries(event.getPos());
    }
}

void StarfallApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
  case ci::app::KeyEvent::KEY_DOWN:
      break;
  case ci::app::KeyEvent::KEY_UP:
      break;
  case ci::app::KeyEvent::KEY_TAB:
      break;
    case ci::app::KeyEvent::KEY_DELETE:
      break;
  }
}

}  // namespace ideal_gas
