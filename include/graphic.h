#pragma once

namespace starfall {
class Graphic {
  public:
    /**
     * Renders a graphic element in Cinder.
     * Is called by draw() in cinder app.
     */
    virtual void Draw() const = 0;

    /**
     * Updates state of a graphic element in Cinder.
     * Is called by update() in cinder app.
     */
    virtual void Update() = 0;

    virtual ~Graphic(void) = default;

  protected:

};
}