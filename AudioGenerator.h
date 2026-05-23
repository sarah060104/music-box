#ifndef SIMPLE_SYNTH_AUDIOGENERATOR_H
#define SIMPLE_SYNTH_AUDIOGENERATOR_H

#include <array>

#include "AudioPlayer.h"
#include "Controller.h"
#include "portaudio.h"
#include "Sequencer.h"

class AudioGenerator {
public:
    void init();
    AudioGenerator(Controller& controller);

    AudioPlayer players[4];

private:
    Controller& controller;
    PaStream* stream = nullptr;
    static int audioCallback( const void *inputBuffer, void *outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo* timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData );
    Sequencer sequencer;


};


#endif //SIMPLE_SYNTH_AUDIOGENERATOR_H
