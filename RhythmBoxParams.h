#ifndef BEATBOX_61601_RHYTHMBOXPARAMS_H
#define BEATBOX_61601_RHYTHMBOXPARAMS_H
#include <vector>
#include <array>
#include <string>


struct RhythmBoxParams {
    bool playing = false;
    int bpm = 120;
    bool grid[4][16]={};
    int currentStep = 0;
    std::array<bool, 4> muted = {};
    std::array<std::string, 4> wavPath;
    std::array<float, 4> volumes= {1.0f, 1.0f, 1.0f, 1.0f};
    std::array<bool, 4> reverse = {};
    std::array<float, 4> delayTime = {0.0f, 0.0f, 0.0f, 0.0f};
    std::array<float, 4> delayMix = {0.0f, 1.0f, 0.0f, 0.0f};
    bool delayActive = false;



};

#endif //BEATBOX_61601_RHYTHMBOXPARAMS_H