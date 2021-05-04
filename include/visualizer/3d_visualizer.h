#pragma once

#include <vector>

namespace audio {
    class Visualizer3D{
    public:
        Visualizer3D();

        /**
          * Works with draw function and will display visual components relating to the magnitude of freqs of audio at a given slice
          */
        void Draw(std::vector<float> magnitudes_of_freq, int y_coordinate) const;
        /**
          * Updates camera position to simulate drone effect
          */
        void Update();
    private:
        float Rescale(float value, float init_low, float init_high, float new_low, float new_high) const;
        int x_coordinate_;
        int z_coordinate_;
    };

}