#include "starfall_app.h"

namespace starfall {

StarfallApp::StarfallApp() {
    current_color_ = ci::Color(0, 255, 0);
    current_trajectory_ = M_PI/4;
}

void StarfallApp::setup() {
    // loads and adds mountains image to app
    auto image = ci::loadImage( "/Users/user/CLionProjects/cinder_0.9.2_mac/"
                                "my_projects/final-project-skyien-z/resources/"
                                "mountains_for_starfall.png");
    background_image_ = ci::gl::Texture2d::create(image);
    setWindowSize(background_image_->getWidth(),
                  background_image_->getHeight());

    // Conform canvas size to image specifications
    canvas_ = Canvas(glm::vec2(0, 0), getWindowWidth(),getWindowHeight());

    // Generate simulation with copy of canvas_
    simulation_ = Simulation(canvas_);
}

void StarfallApp::draw() {
    ci::gl::draw(background_image_);

    if (is_playing_simulation_) {
        // simulation draws on its own canvas
        simulation_.Draw();
    } else {
        canvas_.Draw();
    }
}

void StarfallApp::update() {
    // if simulation is over, this update bool is_playing_simulation_ to false
    if (is_playing_simulation_) {
        simulation_.Update(); // simulation updates its own canvas
        is_playing_simulation_ = simulation_.IsPlayingSimulation();
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
  case ci::app::KeyEvent::KEY_TAB:
    canvas_.RemoveBoundaries();
    break;
  case ci::app::KeyEvent::KEY_SPACE:
      current_color_ = GetRandomColor();
      current_trajectory_ = GetRandomTrajectory();
      break;
  case ci::app::KeyEvent::KEY_UP:
      canvas_.ImportBoundaryPointsFromFile(
              "/Users/user/CLionProjects/cinder_0.9.2_mac/my_projects/"
              "final-project-skyien-z/resources/mountain_boundaries");
      break;
  case ci::app::KeyEvent::KEY_DOWN:
      canvas_.ExportBoundaryPointsToFile(
              "/Users/user/CLionProjects/cinder_0.9.2_mac/my_projects/"
              "final-project-skyien-z/resources/mountain_boundaries");
      break;
  case ci::app::KeyEvent::KEY_RETURN:
      is_playing_simulation_ = true;
      simulation_.StartSimulation();
      break;
  case ci::app::KeyEvent::KEY_BACKSPACE:
      is_playing_simulation_ = false;
      simulation_.EndSimulation();
      break;
  case ci::app::KeyEvent::KEY_RIGHT:
      // Sets trajectory to a random float angle that goes right
      current_trajectory_ = GetRandomFloat(5*M_PI/3, 7*M_PI/3);
      break;
  case ci::app::KeyEvent::KEY_LEFT:
      // Sets trajectory to a random float angle that goes left
      current_trajectory_ = GetRandomFloat(2*M_PI/3, 4*M_PI/3);
      break;
  }

}

}  // namespace starfall
