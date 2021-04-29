#include "visualizer/3d_visualizer.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

namespace audio {
    Visualizer3D::Visualizer3D() {
        x_coordinate_ = 1;
        z_coordinate_ = 1;
    }
    
    void Visualizer3D::Draw(std::vector<float> magnitudes_of_freq) const{
        ci::gl::clear();
        ci::gl::enableDepthRead();
        ci::gl::enableDepthWrite();

        ci::CameraPersp cam;
        cam.lookAt(glm::vec3(15 * cos((x_coordinate_ / 4)), 10, 15 * sin((z_coordinate_ / 4))), glm::vec3(0, 0, 0)); //TODO: rotate camera
        ci::gl::setMatrices(cam);
    //TODO: cite and optimize performance
        float maxAngle = M_PI *
                         20; //TODO: change this from 7 to 20, changing this creates bigger angles, makes it from circles to star shaped
        float anim = cinder::app::getElapsedFrames() / 30.0f;
        for (size_t i = 0; i < magnitudes_of_freq.size(); i++) {
            float rel = i / (float) magnitudes_of_freq.size() *
                        1.5; //TODO: num of spheres, also affects radius and how far out things are positioned
            //TODO: 1.25 vs 1.5
            float angle = rel * maxAngle;
            float h = Rescale(magnitudes_of_freq[i], 0, 0.01, 0,
                            2); //TODO: normalize using max of all slices, right now can reverse by doing minus as index is connected to position for code here so reversing loop changes nothing
            float h2 = Rescale(magnitudes_of_freq[i], 0, 0.01, 0, 1);
            float y =
                    fabs(cos(rel * M_PI + anim)) * h; //TODO: change this 1 variable to represent height, range from 0 to 2
            float r = rel * 5; //TODO: makes radius more spread out, make this a constant //TODO: change this from 2 to 5
            ci::vec3 offset(r * cos(angle), y / 2, r * sin(angle)); //TODO: determines positioning of element
            ci::gl::pushModelMatrix();
            ci::gl::translate(offset); //TODO: positions elements in circle
            ci::gl::scale(glm::vec3(0.05f, y, 0.05f)); //TODO: scales model matrix
            ci::gl::color(ci::Color(cinder::CM_HSV, h2, 1,
                                    1)); //TODO:change this to color based on frequency, help on how to do this 
            ci::gl::drawCube(glm::vec3(), glm::vec3(1)); //TODO: size of cube
            ci::gl::popModelMatrix();
    
    //TODO: take waveform graph/complete iges/any vector and convert it into spectrogram (at time what energy is associated with frequency)
    //TODO: fft over an image(repetitive stuff) --> frequency is shorter
        }
    }
    
    float Visualizer3D::Rescale(float value, float init_low, float init_high, float new_low, float new_high) const {
        return new_low + (value - init_low) * (new_high - new_low) / (init_high - init_low);
    }

    void Visualizer3D::Update() {
        x_coordinate_++;
        z_coordinate_++;
    }

}