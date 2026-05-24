#ifndef BEATBOX_61601_CONTROLLER_H
#define BEATBOX_61601_CONTROLLER_H
#include <mutex>
#include <string>

#include "RhythmBoxParams.h"


class Controller {

    RhythmBoxParams params;
    std::mutex mutex;

public:
    void setPlaying(bool playing);
    void setBpm(int bpm);
    void setStep(int track, int step, bool active);
    void setMute(int track, bool mute);
    void setCurrentStep(int step);
    void registerFileName(int track, std::string path);
    void setVolume(int track,float vol );
    void setReverse(int track,bool reverse);
    RhythmBoxParams getRhythmBoxParams();

};


#endif //BEATBOX_61601_CONTROLLER_H