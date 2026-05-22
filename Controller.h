#ifndef BEATBOX_61601_CONTROLLER_H
#define BEATBOX_61601_CONTROLLER_H
#include <mutex>
#include <string>

#include "RhythmBoxParams.h"


class Controller {

    RhythmBoxParams params;

public:
    void setPlaying(bool playing);
    void setBpm(int);
    void loadFile(std::string);
};


#endif //BEATBOX_61601_CONTROLLER_H