#pragma once
#include <string>
#include "cinder/audio/audio.h"
#include "audio_processor.h"

namespace audio {
    class AudioProcessor{
    public:
        /**
          * Constructor that sets initial state of app and takes in a file path
          */
        AudioProcessor(std::string audio_file_path);

        /**
          * Empty Constructor for testing and taking in user input for songs
          */
        AudioProcessor();

        /**
          * Works with draw function and will display visual components relating to the magnitude of freqs of audio at a given slice
          */
        void Display();

        /**
          * Will update magnitude spectrum to hold new values as song plays real-time 
          */
        void AdvanceOneFrame();
    private:
        cinder::audio::MonitorSpectralNodeRef spectral_;
        std::vector<float> magnitudes_of_freq_;
        cinder::audio::VoiceRef audio_output_;
        float Remap(float value, float init_low, float init_high, float new_low, float new_high) const;
        int x_coordinate_;
        int z_coordinate_;
    };

}  // namespace app
