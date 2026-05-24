#ifndef BEATBOX_61601_SEQUENCER_H
#define BEATBOX_61601_SEQUENCER_H
#include <atomic>


class Sequencer {
    std::atomic<int> currentStep = 1;
    double beatAccum  = 0.0;


public:
    int advance(int numFrames, int sampleRate, int bpm);
    int getCurrentStep() const;




};


#endif //BEATBOX_61601_SEQUENCER_H