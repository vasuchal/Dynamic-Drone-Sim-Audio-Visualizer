#include "visualizer/2d_visualizer.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

namespace audio {
    //TODO: shorten ci::gl
    Visualizer2D::Visualizer2D() = default;
    void Visualizer2D::Draw(std::vector<float> magnitudes_of_freq) const {
        ci::gl::clear();

        // preserve the default Model matrix
        ci::gl::pushModelMatrix();
        // move to the window center
        ci::gl::translate( ci::app::getWindowCenter() );

//        int numCircles = 16;
        float radius = ci::app::getWindowHeight() / 4;

        for( int c = 0; c < (magnitudes_of_freq.size() / 2); c++ ) {
            float rel = c / (float) (magnitudes_of_freq.size() / 2);
            float angle = rel * M_PI * 2;
            ci::vec2 offset( cos( angle ), sin( angle ) );

            // preserve the Model matrix
            ci::gl::pushModelMatrix();
            // move to the correct position
            ci::gl::translate( offset * (radius * 2));
            // set the color using HSV color
            ci::gl::color( ci::Color( ci::CM_HSV, rel, 1, 1 ) );
            // draw a circle relative to Model matrix
            ci::gl::drawStrokedCircle( ci::vec2(), 10 );
            
            float average_freq = (magnitudes_of_freq[c * 2] + magnitudes_of_freq[(c * 2) + 1]) / 2;

            if (average_freq > 0.0001) {
                ci::gl::drawSolidCircle( ci::vec2(),  10);
            } 
            
            // restore the Model matrix
            ci::gl::popModelMatrix();
        }

        // restore the default Model matrix
        ci::gl::popModelMatrix();
    }
}
