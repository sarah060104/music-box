#ifndef BEATBOX_61601_SEQUENCER_H
#define BEATBOX_61601_SEQUENCER_H


class Sequencer {
    int currentStep = 0;
    int bpm = 120;
    bool grid[4][16];

public:
    int advance(int numFrames, int sampleRate, int bpm);
    int getCurrentStep();



};


#endif //BEATBOX_61601_SEQUENCER_H