#pragma once

namespace starfall {
class Graphic {
  public:
    virtual void Draw() const = 0;

    virtual void Update() = 0;

  protected:

};
}