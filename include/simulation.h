#pragma once

#include "canvas.h"

namespace starfall {

/**
 * Displays a simulation of shooting stars with a paragraph
 * description of starfall when given a canvas to "draw" on.
 */
class Simulation: public Graphic{

  public:
    Simulation(const Canvas& canvas);

    void Draw() const;

    void Update();

 private:
    ci::Timer timer_;

    // holds on to all sentence fragments that make up the paragraph
    std::vector<std::string> paragraph_lines_;

    // index of line of paragraph_lines_ that simulation is displaying
    size_t frame_index_;

    void ReadInParagraph(std::string abs_or_relative_file_path);

};
} // namespace starfall

