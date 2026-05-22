#ifndef BEATBOX_61601_RHYTHMBOXPARAMS_H
#define BEATBOX_61601_RHYTHMBOXPARAMS_H
#include <vector>


struct RhythmBoxParams {
    bool playing = false;
    int bpm = 120;
    bool grid[4][16];
    int currentStep = 1;
    std::vector<bool> muted = {false, false, false, false} ;



};


#endif //BEATBOX_61601_RHYTHMBOXPARAMS_H