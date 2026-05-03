#ifndef SIMPLE_SYNTH_AUDIOGENERATOR_H
#define SIMPLE_SYNTH_AUDIOGENERATOR_H

#include <array>

#include "AudioPlayer.h"
#include "portaudio.h"

class AudioGenerator {
public:
    void init();

private:
    static int audioCallback( const void *inputBuffer, void *outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo* timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData );

    std::array<AudioPlayer,4>;
    std::array<float, 4>       volumes = {1,1,1,1};
    std::array<bool,  4>       mutes   = {};

};


#endif //SIMPLE_SYNTH_AUDIOGENERATOR_H
