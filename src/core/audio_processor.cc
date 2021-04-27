#include "cinder/audio/Context.h"
#include "cinder/audio/audio.h"
#include <core/audio_processor.h>
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"


namespace audio {
//TODO: shortening this (no putting cinder)
    using namespace cinder::audio;
    using namespace ci::gl;
    using cinder::app::KeyEvent;
    AudioProcessor::AudioProcessor(std::string file_path) {
        
        audio::SourceFileRef sourceFile = audio::load(cinder::app::loadAsset(file_path));
        auto ctx = cinder::audio::Context::master();
        spectral_ = ctx->makeNode( new audio::MonitorSpectralNode); //capable of fft (calculates everything) storing mag spec 
        auto mBufferPlayer = ctx->makeNode( new audio::BufferPlayerNode());
        mBufferPlayer->loadBuffer(sourceFile);
        mBufferPlayer >> spectral_; //connecting an input to an output
        
        audio_output_ = audio::Voice::create(sourceFile);
        audio_output_->start(); //TODO: implement later
        
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
        cam.lookAt(glm::vec3(4, 4, 4), glm::vec3(0, 0, 0)); //T
        ci::gl::setMatrices(cam);

        
        //TODO: cite and optimize performance
        int numSpheres = 256;
        float maxAngle = M_PI * 7;
        float anim = cinder::app::getElapsedFrames() / 30.0f;
        float red = 0.1;
        float green = 0.3;
        float blue = 0.5;
        for (int s = 0; s < numSpheres; s++) {
            float rel = s / (float) numSpheres;
            float angle = rel * maxAngle;
            float y = fabs(cos(rel * M_PI + anim)) * 1; //TODO: change this 1 variable to represent height, range from 0 to 2
            float r = rel * 2; //TODO: makes radius more spread out, make this a constant
            ci::vec3 offset(r * cos(angle), y / 2, r * sin(angle)); //TODO: determines positioning of element
            ci::gl::pushModelMatrix();
            ci::gl::translate(offset); //TODO: positions elements in circle
            ci::gl::scale(glm::vec3(0.05f,y,0.05f)); //TODO: scales model matrix
            ci::gl::color(red, green, blue); //TODO:change this to color based on frequency 
            ci::gl::drawCube(glm::vec3(), glm::vec3(1)); //TODO: size of cube
            ci::gl::popModelMatrix();
            red = red + 0.005;
            green = green + 0.005;
            blue = blue + 0.005;
        }
    }

    void AudioProcessor::AdvanceOneFrame() {
        magnitudes_of_freq_ = spectral_->getMagSpectrum();
    }
}
