#include "cinder/audio/Context.h"
#include "cinder/audio/audio.h"
#include <core/audio_processor.h>
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"


namespace audio {
//TODO: shortening this
    using namespace cinder::audio;
    using namespace ci::gl;
    using cinder::app::KeyEvent;
    
    AudioProcessor::AudioProcessor(std::string file_path) {
        bin_count_ = 0;
        
        audio::SourceFileRef sourceFile = audio::load(cinder::app::loadAsset(file_path));
        auto ctx = cinder::audio::Context::master();
        spectral_ = ctx->makeNode( new audio::MonitorSpectralNode); //capable of fft (calculates everything) storing mag spec 
        auto mBufferPlayer = ctx->makeNode( new audio::BufferPlayerNode() );
        mBufferPlayer->loadBuffer(sourceFile);
        mBufferPlayer >> spectral_; //connecting an input to an output
        
        audio::VoiceRef mVoice = audio::Voice::create(sourceFile);
        mVoice->start(); //TODO: implement later
        
        ctx->enable();
        mBufferPlayer->enable();
        mBufferPlayer->start();
    }

    AudioProcessor::AudioProcessor() {};

    void AudioProcessor::Display() {
        ci::gl::clear();
        ci::gl::enableDepthRead();
        ci::gl::enableDepthWrite();

        ci::CameraPersp cam;
        cam.lookAt(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0));
        ci::gl::setMatrices(cam);

        auto lambert = ci::gl::ShaderDef().lambert().color();
        auto shader = ci::gl::getStockShader(lambert);
        shader->bind();

        int numSpheres = 128;
        float maxAngle = M_PI * 7;
        float anim = cinder::app::getElapsedFrames() / 30.0f;
        float red = 1;
        float green = 1;
        float blue = 1;
        for (int s = 0; s < numSpheres; ++s) {
            float rel = s / (float) numSpheres;
            float angle = rel * maxAngle;
            float y = fabs(cos(rel * M_PI + anim)) * 1; //TODO: change this 1 to represent height
            float r = rel;
            ci::vec3 offset(r * cos(angle), y / 2, r * sin(angle));
            ci::gl::pushModelMatrix();
            ci::gl::translate(offset);
            ci::gl::scale(glm::vec3(0.05f, y, 0.05f));
            ci::gl::color(0.5, 0.5, 0.5); //TODO:change this to color based on frequency 
            ci::gl::drawCube(glm::vec3(), glm::vec3(1));
            ci::gl::popModelMatrix();
            red++;
            green++;
            blue++;
        }
    }

    void AudioProcessor::AdvanceOneFrame() {
        magnitudes_of_freq_ = spectral_->getMagSpectrum();
        bin_count_ = spectral_->getNumBins();

    }
}
