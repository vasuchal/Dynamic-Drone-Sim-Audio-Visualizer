#pragma once

namespace audio {
    class Visualizer3D{
    public:
        //TODO: add documentation
        Visualizer3D(int x);
        
        Visualizer3D();

        /**
          * Works with draw function and will display visual components relating to the magnitude of freqs of audio at a given slice
          */
        void Display();
    private:
        
    };

}