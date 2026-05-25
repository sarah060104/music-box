#include "Mixer.h"

#include <algorithm>



void Mixer::clear(float* out, int numFrames) {
    for (int i = 0; i < numFrames * 2; i++)
        out[i] = 0.0f;
}

void Mixer::process(const float* trackBuf, float* out, int numFrames, float gain) {
    for (int i = 0; i < numFrames * 2; i++)
        out[i] += trackBuf[i] * gain;
}


