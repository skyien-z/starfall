#include "starfall_app.h"

namespace starfall {

StarfallApp::StarfallApp(){
}

void StarfallApp::draw() {
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
