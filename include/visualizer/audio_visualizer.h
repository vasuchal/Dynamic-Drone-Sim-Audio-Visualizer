#pragma once

#include <core/audio_processor.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/audio/audio.h"

namespace audio {

/**
 * An app for visualizing inputted audio file.
 */
    class AudioVisualizerApp : public ci::app::App {
    public:
        /**
          * Constructor that sets initial state of app
          */
        AudioVisualizerApp();

        /**
          * Called automatically and will implement the visualizer method of the processor
          */
        void draw() override;

        /**
          * Will update the data structure storing relevant information about the frequencies using processor obj.
          */
        void update() override;

        // provided that you can see the entire UI on your screen.
        const int kWindowSize = 875;
        const int kMargin = 100;

    private:
        AudioProcessor processor_;
    };

} 
