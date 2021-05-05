#pragma once

#include <vector>

namespace audio {
    class Visualizer2D{
    public:
        Visualizer2D();

        /**
          * Works with draw function and will display visual components relating to the magnitude of freqs of audio at a given slice
          */
        void Draw(std::vector<float> magnitudes_of_freq) const;
    private:
    };

}