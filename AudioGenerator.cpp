#include <iostream>
#include "AudioGenerator.h"

#include "AudioPlayer.h"

constexpr int FRAMES_PER_BUFFER {256};
constexpr int SAMPLE_RATE {44100};


/**
 * TODO regler issue avec Process finished with exit code 139 (interrupted by signal 11:SIGSEGV), vient de init
 */
void AudioGenerator::init() {

    PaError errorInit = Pa_Initialize();
    if( errorInit != paNoError ) {
        std::cerr << "PortAudio error in Pa_Initialize(): "
                  << Pa_GetErrorText( errorInit ) << std::endl;
        return;
    }

    PaError errorStream;
    PaStream *stream;

    errorStream = Pa_OpenDefaultStream(&stream,
                                       0,
                                       2,
                                       paFloat32,
                                       SAMPLE_RATE,
                                       FRAMES_PER_BUFFER,
                                       audioCallback,
                                       nullptr );

    errorStream = Pa_StartStream( stream );
    if( errorStream != paNoError ) {
        std::cerr << "PortAudio error in Pa_StartStream(): "
                  << Pa_GetErrorText( errorStream ) << std::endl;
    }
}

int AudioGenerator::audioCallback(const void *inputBuffer,
                                  void *outputBuffer,
                                  unsigned long framesPerBuffer,
                                  const PaStreamCallbackTimeInfo *timeInfo,
                                  PaStreamCallbackFlags statusFlags,
                                  void *userData) {

    // DO STUFF WITH OUTPUTBUFFER
    // ... TODO méthode callback

    auto* player = static_cast<AudioPlayer*>(userData);
    float* out = static_cast<float*>(outputBuffer);
    player->getNextFrames(out, framesPerBuffer);

    return 0;
}

