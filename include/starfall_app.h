#pragma once

#include <math.h>
#include "canvas.h"

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/audio/Voice.h"
#include "canvas.h"
#include "utils.h"
#include "simulation.h"

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

    /**
     * Draws cinder elements for simulation.
     */
    void draw() override;

    /**
     * Updates state of cinder element objects.
     */
    void update() override;

    /**
     * Adds star to canvas when mouse is right-clicked.
     *
     * @param event; mouse event that adds star.
     */
    void mouseDown(ci::app::MouseEvent event) override;

    /**
     * When the Shift key is pressed and the mouse is
     * dragged while the left-click buttom is held,
     * adds points of mouse drag to the boundary points
     * of canvas.
     *
     * @param event; mouse event that adds boundary points.
     */
    void mouseDrag(ci::app::MouseEvent event) override;

    /**
     * Alters app state based on user input from keyboard.
     *
     * @param event; key event that changes state of app.
     */
    void keyDown(ci::app::KeyEvent event) override;

 private:
    // Canvas to draw stars
    Canvas canvas_;

    // Paragraph simulation that takes in copy of canvas
    Simulation simulation_;

    ci::gl::Texture2dRef background_image_;

    // State of app adjusted through user input
    ci::Color current_color_;
    float current_trajectory_;
    bool is_playing_simulation_;
};

}  // namespace ideal_gas
