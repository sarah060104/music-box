#ifndef BEATBOX_61601_MIXER_H
#define BEATBOX_61601_MIXER_H

class Mixer {

public:

    void clear(float* out, int numFrames);
    void process(const float* trackBuf, float* out, int numFrames, float gain = 1.0f);

};


#endif //BEATBOX_61601_MIXER_H