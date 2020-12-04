#pragma once

#include <math.h>
#include "canvas.h"

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/audio/Voice.h"
#include "canvas.h"
#include "utils.h"

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

 private:
    Canvas canvas_;

    ci::gl::Texture2dRef background_image_;
    ci::Color current_color_;
    float current_trajectory_;
};

}  // namespace ideal_gas
