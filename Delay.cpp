#include "Delay.h"

#include <algorithm>

constexpr int SAMPLE_RATE       = 44100;
constexpr int FRAMES_PER_BUFFER = 256;
constexpr int DELAY_BUFFER      = SAMPLE_RATE;


Delay::Delay()
    : writeIndex(0), readIndex(0),
      delayTimeInSeconds(0.5f), delayMix(0.5f)
{
    delayBuffer.resize(DELAY_BUFFER, 0.0f);
}

void Delay::setDelayTime(float timeSeconds) {
    delayTimeInSeconds = std::clamp(timeSeconds, 0.01f, 1.0f);
    updateIndices();
}

void Delay::setDelayMix(float mix) {
    delayMix = std::clamp(mix, 0.01f, 0.9f);
}

void Delay::clearBuffer() {
    std::fill(delayBuffer.begin(), delayBuffer.end(), 0.0f);
    writeIndex = 0;
    updateIndices();
}

void Delay::updateIndices() {
    int delaySamples = static_cast<int>(delayTimeInSeconds * SAMPLE_RATE);
    readIndex = writeIndex - delaySamples;
    if (readIndex < 0) {
        readIndex += DELAY_BUFFER;
    }
}

void Delay::process(float* buffer) {
    for (int i = 0; i < FRAMES_PER_BUFFER; ++i) {
        float delayedSample = delayBuffer[readIndex];

        buffer[i] += delayedSample * delayMix;
        delayBuffer[writeIndex] = buffer[i];
        writeIndex = (writeIndex + 1) % DELAY_BUFFER;
        readIndex  = (readIndex + 1) % DELAY_BUFFER;
    }
}
