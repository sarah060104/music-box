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

    int newStep = -1;
    if (snapshot.playing) {
        newStep = engine->sequencer.advance(
            framesPerBuffer, SAMPLE_RATE, snapshot.bpm);

        if (newStep != -1) {
            engine->controller.setCurrentStep(newStep);

            for (int t = 0; t < 4; t++) {
                if (snapshot.grid[t][newStep] && !snapshot.muted[t]) {
                    engine->players[t].setReverse(snapshot.reverse[t]);
                    engine->players[t].trigger();
                }
            }
        }
    }else {
        for (int i = 0; i < 4; i++)
            engine->players[i].stop();
    }

    engine->mixer.clear(outB, framesPerBuffer);
    for (int t = 0; t < 4; t++) {
        float trackBuf[256 * 2] = {};
        engine->players[t].process(trackBuf, framesPerBuffer);
        float gain = snapshot.muted[t] ? 0.0f : snapshot.volumes[t];
        engine->mixer.addTrack(trackBuf, outB, framesPerBuffer, gain);
    }

    return paContinue;
}

