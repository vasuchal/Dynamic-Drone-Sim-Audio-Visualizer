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
        cam.lookAt(glm::vec3(4, 4, 4), glm::vec3(0, 0, 0)); //TODO: rotate camera
        ci::gl::setMatrices(cam);

        
        //TODO: cite and optimize performance
        float maxAngle = M_PI * 20; //TODO: change this from 7 to 20, changing this creates bugger angles
        float anim = cinder::app::getElapsedFrames() / 30.0f;
        for (size_t i = 0; i < magnitudes_of_freq_.size() / 2; i++) { //TODO: 128 spheres //TODO: put frequency on outside or inside? //TODO: change this from whole to factor
            float rel = i / (float) magnitudes_of_freq_.size() * 1.5; //TODO: num of spheres, also affects radius and how far out things are positioned
            //TODO: 1.25 vs 1.5
            float angle = rel * maxAngle;
            float h = Remap(magnitudes_of_freq_[i], 0, 0.005, 0, 2); //TODO: normalize using max of all slices, right now can reverse by doing minus as index is connected to position for code here so reversing loop changes nothing
            float h2 = Remap(magnitudes_of_freq_[i], 0, 0.005, 0, 1); 
            float y = fabs(cos(rel * M_PI + anim)) * h; //TODO: change this 1 variable to represent height, range from 0 to 2
            float r = rel * 5; //TODO: makes radius more spread out, make this a constant //TODO: change this from 2 to 5
            ci::vec3 offset(r * cos(angle), y / 2, r * sin(angle)); //TODO: determines positioning of element
            ci::gl::pushModelMatrix();
            ci::gl::translate(offset); //TODO: positions elements in circle
            ci::gl::scale(glm::vec3(0.05f,y,0.05f)); //TODO: scales model matrix
            //TODO: 0 to 256 -> 0 to 1
            ci::gl::color(ci::Color(cinder::CM_HSV, h2, 1, 1)); //TODO:change this to color based on frequency, help on how to do this 
            ci::gl::drawCube(glm::vec3(), glm::vec3(1)); //TODO: size of cube
            ci::gl::popModelMatrix();

//TODO: take waveform graph/complete iges/any vector and convert it into spectrogram (at time what energy is associated with frequency)
//TODO: fft over an image(repetitive stuff) --> frequency is shorter
        }
    }
    
    void AudioProcessor::AdvanceOneFrame() {
        magnitudes_of_freq_ = spectral_->getMagSpectrum();
    }

    float AudioProcessor::Remap(float value, float init_low, float init_high, float new_low, float new_high) const{
        return new_low + (value - init_low) * (new_high - new_low) / (init_high - init_low);
    }
}
