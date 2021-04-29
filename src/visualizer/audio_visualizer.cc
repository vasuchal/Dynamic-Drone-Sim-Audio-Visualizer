#include <visualizer/audio_visualizer.h>
#include "cinder/audio/audio.h"

namespace audio {

    using namespace cinder::audio;
    AudioVisualizerApp::AudioVisualizerApp() {
        processor_ = AudioProcessor("assets/Montero.wav");
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
    
    //TODO: audio visualizer class combining both functionalities, visual components class 
    //TODO: loading in new audio files, better way than doing all at back
} 

