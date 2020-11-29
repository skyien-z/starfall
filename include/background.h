#pragma once

namespace starfall {
class Background {
  public:
    Background();

    void Draw() const;

  private:
    /**
     * Uploads image from jpg using Cinder
     */
    void UploadImage();

};
}
