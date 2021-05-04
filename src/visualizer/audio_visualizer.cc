#include <visualizer/audio_visualizer.h>
#include "cinder/audio/audio.h"

namespace audio {

    using namespace cinder::audio;
    AudioVisualizerApp::AudioVisualizerApp() {
        processor_ = AudioProcessor("MoBamba.wav");
        ci::app::setWindowSize(kWindowSize, kWindowSize);
        y_coordinate_ = k3DYCoordinate;
    }

    void AudioVisualizerApp::draw() {
        ci::Color background_color("black");
        ci::gl::clear(background_color);
        processor_.Display(y_coordinate_);
    }

    void AudioVisualizerApp::update() {
        processor_.AdvanceOneFrame();
    }

    void AudioVisualizerApp::keyDown(ci::app::KeyEvent event) {
        switch (event.getCode()) {
            case ci::app::KeyEvent::KEY_2: {
                y_coordinate_ = k2DYCoordinate;
                break;
            }

            case ci::app::KeyEvent::KEY_3: {
                y_coordinate_ = k3DYCoordinate;
                break;

            }
        }
    }
} 

