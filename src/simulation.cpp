#include "simulation.h"

namespace starfall {

Simulation::Simulation(const Canvas &canvas) : canvas_(canvas) {
    ReadInParagraph("resources/starfall_paragraph"); //TODO: check if relative or absolute filepath
    timer_.start();
    frame_index_ = kBeginningFrame;
}

void Simulation::Draw() const {

}

void Simulation::Update() {
//    if (!timer_.isStopped()) {
//        timer_.start();
//    }

}

void Simulation::ReadInParagraph(std::string abs_or_relative_file_path) {
    std::ifstream text_stream (abs_or_relative_file_path);

    std::string next_line;
    while (!text_stream.eof()) {
        std::getline(text_stream, next_line);

        paragraph_lines_.push_back(next_line);
    }
}

void Simulation::ClearSimulation() {
    frame_index_ = kBeginningFrame;

    // Sets timer to
    timer_ = ci::Timer(false);
}

} // namespace starfall