#include "simulation.h"

namespace starfall {

Simulation::Simulation(Canvas canvas) : canvas_(canvas) {
    ReadInParagraph("/Users/user/CLionProjects/cinder_0.9.2_mac/my_projects/"
                    "final-project-skyien-z/resources/starfall_paragraph");

    canvas_.ImportBoundaryPointsFromFile("/Users/user/CLionProjects/"
                             "cinder_0.9.2_mac/my_projects/final-project-skyien-z/"
                             "resources/mountain_boundaries");
    // Calculate star spawning bounds
    star_spawn_left_edge = canvas_.GetLeftEdge();
    // Gets x value in middle of graph
    star_spawn_right_edge = (canvas_.GetRightEdge() - canvas_.GetLeftEdge())/2;
    star_spawn_bottom_edge = canvas_.GetBottomEdge(); // lowest y value
    star_spawn_top_edge = canvas_.GetBottomEdge() + 60;
}

void Simulation::ReadInParagraph(const std::string &absolute_file_path) {
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
    is_playing_simulation = true;
    text_color_alpha_ = 0;
}

void Simulation::Draw() const {
    if (!is_playing_simulation) {
        return;
    }

    glm::vec2 string_position ((canvas_.GetRightEdge() -
    canvas_.GetLeftEdge())/2,canvas_.GetBottomEdge() + 50);

    ci::gl::drawStringCentered(paragraph_lines_[frame_index_], string_position,
     ci::ColorA(255, 255, 255, text_color_alpha_),
     ci::Font("Apple Chancery", 16));

    canvas_.Draw();
}

void Simulation::Update() {
    if (!is_playing_simulation) {
        return;
    }
    // if all frames have been displayed
    if (frame_index_ == paragraph_lines_.size()) {
        EndSimulation();
        return;
    }

    int current_second = floor(timer_.getSeconds());
    bool isWholeSecond = timer_.getSeconds() - current_second <= 0.01;

    // If statement which updates frame and generates a star is
    // run every 2 seconds (value of kSecondsForFrameChange)
    if (isWholeSecond && current_second % kSecondsForFrameChange == 1) {
        frame_index_++;
        text_color_alpha_ = 0; // new text line starts transparent to fade in

        // Generates a star with trajectory going right and down
        GenerateStarInBounds(GetRandomFloat(0, M_PI/3));
    } else {
        // creates text fading in effect by increasing text opacity as time goes on
        text_color_alpha_ += 0.05;
    }
    // Ensures that a star is released every second (runs the second
    // after above if statement runs)
    if (isWholeSecond && current_second % kSecondsForFrameChange == 0) {
        GenerateStarInBounds(M_PI/3);
    }
    canvas_.Update();
}

void Simulation::GenerateStarInBounds(float trajectory) {
    glm::vec2 starting_position = GetRandomStartingPosition(
            star_spawn_left_edge, star_spawn_right_edge,
            star_spawn_bottom_edge, star_spawn_top_edge);
    canvas_.AddStarToList(starting_position, GetRandomColor(),
                          trajectory);
}

void Simulation::EndSimulation() {
    timer_.stop();
    is_playing_simulation = false;
}

const std::vector<std::string> &Simulation::GetParagraphLines() {
    return paragraph_lines_;
}

bool Simulation::IsPlayingSimulation() const {
    return is_playing_simulation;
}

} // namespace starfall