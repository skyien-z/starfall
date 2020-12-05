#include "starfall_app.h"

namespace starfall {

StarfallApp::StarfallApp() {
    addAssetDirectory("/Users/user/CLionProjects/cinder_0.9.2_mac/"
                      "my_projects/final-project-skyien-z/resources/");

    current_color_ = ci::Color(0, 255, 0);
    current_trajectory_ = M_PI/4;
}

void StarfallApp::draw() {
    ci::gl::draw(background_image_);

    if (is_playing_simulation_) {
        // the canvas is drawn in the simulation
        simulation_.Draw();
    } else {
        canvas_.Draw();
    }
}

void StarfallApp::setup() {
    auto image = ci::loadImage( "/Users/user/CLionProjects/cinder_0.9.2_mac/my_projects/"
                                "final-project-skyien-z/resources/mountains_for_starfall.png");
    background_image_ = ci::gl::Texture2d::create(image);
    setWindowSize(background_image_->getWidth(),
                  background_image_->getHeight());

    // Conform canvas size to image specifications
    canvas_ = Canvas(glm::vec2(0, 0), getWindowWidth(),getWindowHeight());
    simulation_ = Simulation(canvas_);
}

void StarfallApp::update() {
    if (is_playing_simulation_) {
        simulation_.Update();
    } else {
        canvas_.Update();
    }
}

void StarfallApp::mouseDown(ci::app::MouseEvent event) {
    if (event.isRightDown()) {
        canvas_.AddStarToList(event.getPos(), current_color_,
                              current_trajectory_);
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
      current_color_ = GetRandomColor();
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
  case ci::app::KeyEvent::KEY_TAB:
    canvas_.RemoveBoundaries();
    break;
  case ci::app::KeyEvent::KEY_SPACE:
      current_color_ = GetRandomColor();
      current_trajectory_ = GetRandomTrajectory();
  case ci::app::KeyEvent::KEY_RETURN:
      is_playing_simulation_ = true;
      simulation_.StartSimulation();
      break;
  case ci::app::KeyEvent::KEY_RIGHT:
      current_trajectory_ = GetRandomRightTrajectory();
      break;
  case ci::app::KeyEvent::KEY_LEFT:
      current_trajectory_ = GetRandomLeftTrajectory();
      break;
  }

}

}  // namespace ideal_gas
