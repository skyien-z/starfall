#include "starfall_app.h"

namespace starfall {

StarfallApp::StarfallApp(): canvas_(glm::vec2(kMargin, kMargin),
              kWindowSize, kMargin) {
        ci::app::setWindowSize((int) kWindowSize + kMargin,
                               (int) kWindowSize - kMargin);
}

void StarfallApp::draw() {
    ci::Color8u background_color(0, 0, 0);
    ci::gl::clear(background_color);
}

void StarfallApp::setup() {
}

void StarfallApp::update() {
}

void StarfallApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
  case ci::app::KeyEvent::KEY_DOWN:
      break;
  case ci::app::KeyEvent::KEY_UP:
      break;
  case ci::app::KeyEvent::KEY_TAB:
      break;
    case ci::app::KeyEvent::KEY_1:
        break;
  case ci::app::KeyEvent::KEY_2:
      break;
  case ci::app::KeyEvent::KEY_3:
      break;
    case ci::app::KeyEvent::KEY_DELETE:
      break;
  }
}

}  // namespace ideal_gas
