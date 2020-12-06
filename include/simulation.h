#pragma once

#include "canvas.h"
#include "utils.h"

namespace starfall {

/**
 * Displays a simulation of shooting stars with a paragraph
 * description of starfall when given a canvas to "draw" on.
 */
class Simulation : public Graphic {

  public:
    /**
     * Explicit constructor of simulation that accepts
     * a canvas object
     * @param canvas on which to draw simulation
     */
    Simulation(Canvas canvas);

    Simulation() = default;

    /**
     * Draws paragraph lines and simulation canvas when
     * simulation plays
     */
    void Draw() const;

    /**
     * Updates paragraph line displayed based on timer and adds
     * stars to simulation canvas based on timer. Updates canvas
     * each time called.
     */
    void Update();

    /**
     * Starts simulation by starting timer and setting
     * simulation states back to their beginning positions.
     */
    void StartSimulation();

    /**
     * Stops timers and sets is_playing_simulation to false.
     */
    void EndSimulation();

    /**
     * Returns whether the simulation is in progress
     *
     * @return true if simulation is playing, false otherwise
     */
    bool IsPlayingSimulation() const;

    const std::vector<std::string>& GetParagraphLines();

private:
    Canvas canvas_;
    ci::Timer timer_;
    bool is_playing_simulation;

    // alpha value of text color
    float text_color_alpha_;

    static constexpr size_t kBeginningFrame = 0;
    static constexpr size_t kSecondsForFrameChange = 2;

    // bounds used to generate star starting position
    float star_spawn_left_edge;
    float star_spawn_right_edge;
    float star_spawn_top_edge;
    float star_spawn_bottom_edge;

    // holds on to all sentence fragments that make up the paragraph
    std::vector<std::string> paragraph_lines_;

    // index of line of paragraph_lines_ that simulation is displaying
    size_t frame_index_;

    /**
     * Read in text from absolute_file_path into paragraph_lines_
     * vector.
     *
     * @param absolute_file_path
     */
    void ReadInParagraph(const std::string &absolute_file_path);

    /**
     * Adds a random star to the canvas object held by simulation.
     * @param trajectory
     */
    void GenerateStarInBounds(float trajectory);
};
} // namespace starfall

