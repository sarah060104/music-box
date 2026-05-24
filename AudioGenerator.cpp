#include <iostream>
#include "AudioGenerator.h"

#include "AudioPlayer.h"
#include "RhythmBoxParams.h"

constexpr int FRAMES_PER_BUFFER {256};
constexpr int SAMPLE_RATE {44100};


AudioGenerator::AudioGenerator(Controller& controller)
    : controller(controller) {}

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
                                        this ); //TODO pointeur vers donnée


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
    auto* engine = static_cast<AudioGenerator*>(userData);  // récupère this
    auto* outB   = static_cast<float*>(outputBuffer);

    RhythmBoxParams snapshot = engine->controller.getRhythmBoxParams();

    for (int i = 0; i < 4; i++) {
        if (snapshot.wavPath[i] != engine->loadedPaths[i]) {
            engine->loadedPaths[i] = snapshot.wavPath[i];
            if (!snapshot.wavPath[i].empty())
                engine->players[i].loadWav(snapshot.wavPath[i]);
        }
    }

    float trackBuf[256 * 2] = {};

    int newStep = -1;
    if (snapshot.playing) {
        newStep = engine->sequencer.advance(
        framesPerBuffer, SAMPLE_RATE, snapshot.bpm);

        if (newStep != -1) {
            engine->controller.setCurrentStep(newStep);

            if (snapshot.grid[0][newStep] &&!snapshot.muted[0]) {
                engine->players[0].trigger();
            }
        }
    }else {
        for (int i = 0; i < 4; i++) {
            engine->players[i].stop();
        }
    }

    engine->players[0].process(trackBuf, framesPerBuffer);

    for (int i = 0; i < (int)framesPerBuffer * 2; i++)
        outB[i] = trackBuf[i];

    return paContinue;
}

