#ifndef BEATBOX_61601_DELAY_H
#define BEATBOX_61601_DELAY_H
#include <vector>


class Delay {

public:
    Delay();
    void setDelayTime(float timeSeconds);
    void setDelayMix(float mix);
    void clearBuffer();
    void process(float* buffer);

private:
    std::vector<float> delayBuffer;
    int writeIndex;
    int readIndex;
    float delayTimeInSeconds;
    float delayMix;
    void updateIndices();

};


#endif //BEATBOX_61601_DELAY_H
