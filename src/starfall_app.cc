#include "starfall_app.h"

namespace starfall {

StarfallApp::StarfallApp():
canvas_(glm::vec2(5*kMargin, kMargin),
          kWindowSize - 4 * kMargin, kMargin) {
ci::app::setWindowSize((int) kWindowSize + 2*kMargin,
                       (int) kWindowSize - kMargin);
}

void StarfallApp::draw() {
  ci::Color8u background_color(194, 255, 255);
  ci::gl::clear(background_color);

  canvas_.Draw();
}

void StarfallApp::setup() {
    for (int i = 0; i < 2; i++) {
        canvas_.AddRandomPositionParticle(5, 0.5, "red");
        canvas_.AddRandomPositionParticle(8, 1, "blue");
        canvas_.AddRandomPositionParticle(9, 2, "green");
    }
}

void StarfallApp::update() {
    canvas_.Update();
}

void StarfallApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
  case ci::app::KeyEvent::KEY_DOWN:
      canvas_.ScaleVelocity(0.9);
      break;
  case ci::app::KeyEvent::KEY_UP:
      canvas_.ScaleVelocity(1.1);
      break;
  case ci::app::KeyEvent::KEY_TAB:
      canvas_.RemoveOneParticle();
      break;
    case ci::app::KeyEvent::KEY_1:
        canvas_.AddRandomPositionParticle(5, 0.5, "red");
        break;
  case ci::app::KeyEvent::KEY_2:
      canvas_.AddRandomPositionParticle(8, 1, "blue");
      break;
  case ci::app::KeyEvent::KEY_3:
      canvas_.AddRandomPositionParticle(9, 2, "green");
      break;
    case ci::app::KeyEvent::KEY_DELETE:
      canvas_.Clear();
      break;
  }
}

}  // namespace ideal_gas
