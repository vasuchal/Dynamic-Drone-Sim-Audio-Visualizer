#pragma once

#include "core/audio_processor.h"
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

        /**
          * Allows users to select 2d or 3d visualization.
          */
        void keyDown(ci::app::KeyEvent event) override;

        // provided that you can see the entire UI on your screen.
        const int kWindowSize = 875;

    private:
        static const int k3DYCoordinate = 10;
        static const int k2DYCoordinate = 0;
        const std::string audio_file_name = "Montero.wav";
        
        AudioProcessor processor_;
        int y_coordinate_;
        bool is_playing_;
    };

} 
