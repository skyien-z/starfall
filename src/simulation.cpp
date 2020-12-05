#include "simulation.h"

namespace starfall {

Simulation::Simulation(const Canvas &canvas) : canvas_(canvas) {
    ReadInParagraph("resources/starfall_paragraph"); //TODO: check if relative or absolute filepath

    // Calculate star spawning bounds
    star_spawn_left_edge = canvas_.GetLeftEdge();
    // Gets x value in middle of graph
    star_spawn_right_edge = (canvas_.GetRightEdge() - canvas_.GetLeftEdge())/2;
    star_spawn_bottom_edge = canvas_.GetTopEdge(); // gets lowest y value
    // Gets y value in middle of graph
    star_spawn_top_edge = (canvas_.GetBottomEdge() - canvas_.GetTopEdge())/2;
}

void Simulation::ReadInParagraph(std::string abs_or_relative_file_path) {
    std::ifstream text_stream (abs_or_relative_file_path);

    std::string next_line;
    while (!text_stream.eof()) {
        std::getline(text_stream, next_line);

        paragraph_lines_.push_back(next_line);
    }
}

void Simulation::StartSimulation() {
    // "Resets" the timer if simulation was run before
    timer_.start(0);
    frame_index_ = kBeginningFrame;
}

void Simulation::Draw() const {

}

void Simulation::Update() {
    int current_second = floor(timer_.getSeconds());
    bool isWholeSecond = timer_.getSeconds() - current_second <= 0.0001;

    // Increments frame (changes line displayed) every kSecondsForFrameChange
    if (isWholeSecond && current_second % kSecondsForFrameChange == 0) {
        frame_index_++;
    }

}

void Simulation::GenerateStarInBounds() {
    glm::vec2 starting_position = GetRandomStartingPosition(
            star_spawn_left_edge, star_spawn_right_edge,
            star_spawn_bottom_edge, star_spawn_top_edge);
    canvas_.AddStarToList(starting_position, GetRandomColor(),
                          GetRandomLeftTrajectory());
}

void Simulation::EndSimulation() {
    timer_.stop();
}

} // namespace starfall