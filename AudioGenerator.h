#ifndef SIMPLE_SYNTH_AUDIOGENERATOR_H
#define SIMPLE_SYNTH_AUDIOGENERATOR_H

#include <array>

#include "AudioPlayer.h"
#include "portaudio.h"

class AudioGenerator {
public:
    void init();
    AudioPlayer players[4];

private:
    PaStream* stream = nullptr;
    static int audioCallback( const void *inputBuffer, void *outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo* timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData );



};


#endif //SIMPLE_SYNTH_AUDIOGENERATOR_H
