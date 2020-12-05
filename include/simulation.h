#pragma once

#include "canvas.h"
#include "utils.h"

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

    void StartSimulation();

    void EndSimulation();

    const std::vector<std::string>& GetParagraphLines();

private:
    Canvas canvas_;
    ci::Timer timer_;
    bool is_simulation_over;

    static constexpr size_t kBeginningFrame = 0;
    static constexpr size_t kSecondsForFrameChange = 2;

    float star_spawn_left_edge;
    float star_spawn_right_edge;
    float star_spawn_top_edge;
    float star_spawn_bottom_edge;

    // holds on to all sentence fragments that make up the paragraph
    std::vector<std::string> paragraph_lines_;

    // index of line of paragraph_lines_ that simulation is displaying
    size_t frame_index_;

    void ReadInParagraph(std::string absolute_file_path);

    void GenerateStarInBounds();
};
} // namespace starfall

