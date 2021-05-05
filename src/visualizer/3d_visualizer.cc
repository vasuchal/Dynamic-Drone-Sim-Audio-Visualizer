#include "visualizer/3d_visualizer.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

namespace audio {
    
    Visualizer3D::Visualizer3D() {
        x_coordinate_ = 1;
        z_coordinate_ = 1;
    }
    
    void Visualizer3D::Draw(std::vector<float> magnitudes_of_freq, int y_coordinate) const {
        ci::gl::clear();
        ci::gl::enableDepthRead();
        ci::gl::enableDepthWrite();

        ci::CameraPersp cam;
        cam.lookAt(glm::vec3(15 * cos((x_coordinate_ / 4)), y_coordinate, 15 * sin((z_coordinate_ / 4))), glm::vec3(0, 0, 0));
        ci::gl::setMatrices(cam);

        float maxAngle = M_PI *
                         20; 
        float anim = cinder::app::getElapsedFrames() / 30.0f;
        for (size_t i = 0; i < magnitudes_of_freq.size(); i++) {
            float rel = i / (float) magnitudes_of_freq.size() *
                        1.5; 
            float angle = rel * maxAngle;
            float h = Rescale(magnitudes_of_freq[i], 0, 0.01, 0,
                            2); 
            float h2 = Rescale(magnitudes_of_freq[i], 0, 0.01, 0, 1);
            float y = fabs(cos(rel * M_PI + anim)) * h; 
            float r = rel * 5; 
            ci::vec3 offset(r * cos(angle), y / 2, r * sin(angle)); 
            ci::gl::pushModelMatrix();
            ci::gl::translate(offset); 
            ci::gl::scale(glm::vec3(0.05f, y, 0.05f));
            ci::gl::color(ci::Color(cinder::CM_HSV, h2, 1,
                                    1)); 
            ci::gl::drawCube(glm::vec3(), glm::vec3(1)); 
            ci::gl::popModelMatrix();
            
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