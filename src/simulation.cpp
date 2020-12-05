#include "simulation.h"

namespace starfall {

Simulation::Simulation(const Canvas &canvas) : canvas_(canvas) {
    ReadInParagraph("/Users/user/CLionProjects/cinder_0.9.2_mac/"
                    "my_projects/final-project-skyien-z/resources/starfall_paragraph");

    // Calculate star spawning bounds
    star_spawn_left_edge = canvas_.GetLeftEdge();
    // Gets x value in middle of graph
    star_spawn_right_edge = (canvas_.GetRightEdge() - canvas_.GetLeftEdge())/2;
    star_spawn_bottom_edge = canvas_.GetBottomEdge(); // gets lowest y value
    // Gets y value in middle of graph
    star_spawn_top_edge = (canvas_.GetTopEdge() - canvas_.GetBottomEdge())/2;
}

void Simulation::ReadInParagraph(std::string absolute_file_path) {
    std::ifstream text_stream (absolute_file_path);

    std::string next_line;
    while (!text_stream.eof()) {
        std::getline(text_stream, next_line);

        paragraph_lines_.push_back(next_line);
    }
    text_stream.close();
}

void Simulation::StartSimulation() {
    // "Resets" the timer if simulation was run before
    timer_.start(0);
    frame_index_ = kBeginningFrame;
    is_simulation_over = false;
}

void Simulation::Draw() const {
    if (!is_simulation_over) {

    }
}

void Simulation::Update() {
    if (is_simulation_over) {
        return;
    }

    // if all frames have been displayed
    if (frame_index_ == paragraph_lines_.size()) {
        EndSimulation();
        return;
    }

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
    is_simulation_over = true;
}

const std::vector<std::string> &Simulation::GetParagraphLines() {
    return paragraph_lines_;
}

} // namespace starfall