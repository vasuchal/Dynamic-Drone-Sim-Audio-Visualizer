//
// Created by Vasu Chalasani on 4/21/21.
//

#include "../../include/visualizer/audio_visualizer.h"
namespace audio {

    AudioVisualizerApp::AudioVisualizerApp() {
        //TODO: how to get rid of large path
        processor_ = AudioProcessor("/Users/vasudhachalasani/CLionProjects/Cinder/my-projects/final-project-vasuchal/audio_files/CantinaBand60.wav");
        ci::app::setWindowSize(kWindowSize, kWindowSize);
    }

    void AudioVisualizerApp::draw() {
        ci::Color background_color("black");
        ci::gl::clear(background_color);
        processor_.Display();
    }

    void AudioVisualizerApp::update() {
        processor_.AdvanceOneFrame();
    }

} 