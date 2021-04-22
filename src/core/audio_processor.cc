#include <cinder/audio/Context.h>
#include "cinder/audio/audio.h"
#include "../../include/core/audio_processor.h"

namespace audio {

    using namespace cinder::audio;
    AudioProcessor::AudioProcessor(std::string file_path) {
        bin_count_ = 0;
        audio::SourceFileRef sourceFile = audio::load(cinder::loadFile(file_path ) );
        audio::VoiceRef audio_output = audio::Voice::create(sourceFile);
        auto ctx = audio::Context::master();
        auto monitor_format = audio::MonitorSpectralNode::Format().fftSize(1024).windowSize(512);
        spectral_ = ctx->makeNode( new audio::MonitorSpectralNode(monitor_format));
        audio_output-> getOutputNode() >> spectral_;
        ctx->enable();
        audio_output->start();
        spectral_->setSmoothingFactor(1);
    }

    AudioProcessor::AudioProcessor() {};

    void AudioProcessor::Display() {
        
    }

    void AudioProcessor::AdvanceOneFrame() {
        magnitudes_of_freq_ = spectral_->getMagSpectrum();
        bin_count_ = spectral_->getNumBins();

    }
}
