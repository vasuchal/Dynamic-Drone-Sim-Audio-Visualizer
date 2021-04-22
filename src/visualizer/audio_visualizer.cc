//
// Created by Vasu Chalasani on 4/21/21.
//

#include "../../include/visualizer/audio_visualizer.h"
//TODO: linker errors
namespace audio {

    AudioVisualizerApp::AudioVisualizerApp() {
        processor_ = AudioProcessor();
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