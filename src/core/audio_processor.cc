#include "cinder/audio/Context.h"
#include "cinder/audio/audio.h"
#include <core/audio_processor.h>
#include "visualizer/3d_visualizer.h"
#include "cinder/app/App.h"


namespace audio {
//TODO: shortening this (no putting cinder)
    using namespace cinder::audio;
    using cinder::app::KeyEvent;
    AudioProcessor::AudioProcessor(std::string file_path) {
        visualizer_ = Visualizer3D();

        audio::SourceFileRef sourceFile = audio::load(cinder::app::loadAsset(file_path));
        auto ctx = cinder::audio::Context::master();
        spectral_ = ctx->makeNode( new audio::MonitorSpectralNode); //capable of fft (calculates everything) storing mag spec 
        auto mBufferPlayer = ctx->makeNode( new audio::BufferPlayerNode());
        mBufferPlayer->loadBuffer(sourceFile);
        mBufferPlayer >> spectral_; //connecting an input to an output
        
        audio_output_ = audio::Voice::create(sourceFile);
        audio_output_->start(); 
        
        ctx->enable();
        mBufferPlayer->enable();
        mBufferPlayer->start();
    }

    AudioProcessor::AudioProcessor() = default;

    void AudioProcessor::Display() {
        visualizer_.Draw(magnitudes_of_freq_);
    }
    
    void AudioProcessor::AdvanceOneFrame() {
        magnitudes_of_freq_ = spectral_->getMagSpectrum();
        visualizer_.Update();
    }
    
}
