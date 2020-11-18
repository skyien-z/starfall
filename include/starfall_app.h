#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

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
  void keyDown(ci::app::KeyEvent event) override;

  static constexpr double kWindowSize = 800;
  static constexpr double kMargin = 50;

 private:
};

}  // namespace ideal_gas
