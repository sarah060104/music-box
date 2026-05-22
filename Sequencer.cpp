#include "Sequencer.h"


int Sequencer::advance(int numFrames, int sampleRate, int bpm) {
    double secondsElapsed = (double)numFrames / sampleRate;
    double beatsElapsed   = (secondsElapsed * 60 )/ bpm;

    beatAccum += beatsElapsed;

    if (beatAccum >= 0.25) {
        beatAccum -= 0.25;
        currentStep = (currentStep + 1) % 16;
        return currentStep;
    }
    return -1;
}
int Sequencer::getCurrentStep() const{
     return currentStep;
}

