#pragma once
#include <string>
#include "cinder/audio/audio.h"
#include "audio_processor.h"

namespace audio {
    class AudioProcessor{
    public:
        AudioProcessor(std::string audio_file_path);
        AudioProcessor();
        void Display();
        void AdvanceOneFrame();
    private:
        cinder::audio::MonitorSpectralNodeRef spectral_;
        int bin_count_;
        std::vector<float> magnitudes_of_freq_;
    };

}  // namespace app
