#include "simulation.h"

namespace starfall {

Simulation::Simulation(const Canvas &canvas) : canvas_(canvas) {
    ReadInParagraph("resources/starfall_paragraph"); //TODO: check if relative or absolute filepath
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

}

void Simulation::EndSimulation() {
    timer_.stop();
}

} // namespace starfall