#include "AudioPlayer.h"

#include <algorithm>
#include <iostream>

#include "AudioFileReader.h"
#include <fmt/core.h>


void AudioPlayer::loadWav(const std::string& path) {
    int channel;
    AudioFileReader::loadFile(path, 44100, buffer, channel );

    position = 0;
    playing = false;
}

void AudioPlayer::play() {
    if (buffer.empty()) return;

    playing = true;


    for (const auto& sample : buffer) {
        std::cout << fmt::format("{:6.4f}", applyVolumeToSample(sample)) << std::endl;
    }


    position = reverse ? buffer.size() - 1 : 0;
}

void AudioPlayer::stop() {
    playing = false;
}


void AudioPlayer::setVolume(float v) {
    volume = std::clamp(v, 0.0f, 1.0f);
}

void AudioPlayer::setReverse(bool r) {
    reverse = r;
}

void AudioPlayer::getNextFrames(float* out, int numFrames) {

    for (int i = 0; i < numFrames; i++) {

        if (!playing || buffer.empty()) {
            out[i] = 0.0f;
        }

        float sample = buffer[position];

        out[i] = applyVolumeToSample(sample);

        if (reverse) {
            position--;
        } else {
            position++;
        }

        if (position < 0 || position >= static_cast<int>(buffer.size())) {
            playing = false;
        }
    }
}


float AudioPlayer::applyVolumeToSample(float sample) const {
    using std::max, std::min;
    return max(-1.0f, min(1.0f, sample * volume));
}

