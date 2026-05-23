#ifndef BEATBOX_61601_RHYTHMBOXPARAMS_H
#define BEATBOX_61601_RHYTHMBOXPARAMS_H
#include <vector>
#include <array>
#include <string>


struct RhythmBoxParams {
    bool playing = false;
    int bpm = 120;
    bool grid[4][16]={};
    int currentStep = 1;
    std::array<bool, 4> muted ;
    std::array<std::string, 4> wavPath;



};


#endif //BEATBOX_61601_RHYTHMBOXPARAMS_H