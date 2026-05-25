#include "AudioPlayer.h"

#include <iostream>

#include "AudioFileReader.h"
#include "AudioConstants.h"



AudioPlayer::AudioPlayer() {
}

void AudioPlayer::stop() {
    playing = false;
}

void AudioPlayer::setReverse(bool reversed) {
    reverse = reversed;
}

void AudioPlayer::loadWav(const std::string& path) {
    AudioFileReader::loadFile(path, 44100, buffer, channels);
}


void AudioPlayer::trigger() {
    if (buffer.empty()) return;
    position = reverse ? (int)buffer.size() / channels - 1 : 0;
    playing = true;
}

void AudioPlayer::process(float* out, int numFrames) {
for (int f = 0; f < numFrames; f++) {
        if (!playing) {
            out[f * 2]     = 0.0f;
            out[f * 2 + 1] = 0.0f;
            continue;
        }

        if (channels == 2) {
            out[f * 2]     = buffer[position * 2];
            out[f * 2 + 1] = buffer[position * 2 + 1];
        } else {
            float s = buffer[position];
            out[f * 2]     = s;
            out[f * 2 + 1] = s;
        }

        position += reverse ? -1 : 1;

        bool ended = reverse ? position < 0
                             : position >= (int)buffer.size() / channels;
        if (ended) {
            position = 0;
            playing = false;
        }
    }
}