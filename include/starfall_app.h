#pragma once
#include "canvas.h"

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "canvas.h"

namespace starfall {

/**
 * Cinder app displaying simulation of shooting stars.
 */
class StarfallApp : public ci::app::App {
 public:
  StarfallApp();

  void setup() override;
  void draw() override;
  void update() override;

  //void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

  static constexpr double kWindowSize = 700;
  static constexpr double kMargin = 50;

 private:
    Canvas canvas_;
    ci::gl::Texture2dRef background_image_;

};

}  // namespace ideal_gas
