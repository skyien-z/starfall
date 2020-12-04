#pragma once

#include <math.h>
#include "canvas.h"

#include "cinder/app/App.h"
#include "cinder/audio/Voice.h"
#include "cinder/app/RendererGl.h"
#include "canvas.h"

namespace starfall {

/**
 * Cinder app displaying simulation of shooting stars.
 */
class StarfallApp : public ci::app::App {
  public:
    StarfallApp();

    /**
    * Sets up background images, and from that, the app canvas.
    */
    void setup() override;
    void draw() override;
    void update() override;

    void mouseDown(ci::app::MouseEvent event) override;
    void mouseDrag(ci::app::MouseEvent event) override;
    void keyDown(ci::app::KeyEvent event) override;

    static constexpr double kWindowSize = 700;
    static constexpr double kMargin = 50;

 private:
    // A formalized map of possible trajectories to launch star from
    std::unordered_map<int, double> trajectory_selection_;

    Canvas canvas_;

    ci::gl::Texture2dRef background_image_;
    ci::Color current_color_;

    // Key value of current trajectory value set
    float current_trajectory_key_;
};

}  // namespace ideal_gas
