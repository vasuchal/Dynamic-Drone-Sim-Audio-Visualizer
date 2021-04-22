#include <visualizer/audio_visualizer.h>

using audio::AudioVisualizerApp;

void prepareSettings(AudioVisualizerApp::Settings* settings) {
    settings->setResizable(false);
    //TODO: edit settings
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(AudioVisualizerApp, ci::app::RendererGl, prepareSettings);
