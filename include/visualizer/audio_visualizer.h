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
        AudioVisualizerApp();

        void draw() override;
        void update() override;

        // provided that you can see the entire UI on your screen.
        const int kWindowSize = 875;
        const int kMargin = 100;

    private:
        AudioProcessor processor_;
    };

} 
