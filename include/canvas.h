#pragma once
#include "cinder/gl/gl.h"

class Canvas {
    public:
        Canvas(const glm::vec2& top_left_corner, double canvas_size, double margin);

        void Draw() const;

    private:

};
