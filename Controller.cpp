#include "Controller.h"

#include "AudioFileReader.h"


void Controller::setPlaying(bool playing) {
    std::lock_guard<std::mutex> lock(mutex);

    params.playing = playing;
}
void Controller::setBpm(int bpm) {
    std::lock_guard<std::mutex> lock(mutex);
    params.bpm = bpm;

}


void Controller::setStep(int track, int step, bool active) {
    std::lock_guard<std::mutex> lock(mutex);
    params.grid[track][step] = active;
}

void Controller::setMute(int track, bool mute) {
    std::lock_guard<std::mutex> lock(mutex);
    params.muted[track] = mute;
}

void Controller::setCurrentStep(int step) {
    std::lock_guard<std::mutex> lock(mutex);
    params.currentStep = step;
}

void Controller::registerFileName(int track, std::string path) {
    std::lock_guard<std::mutex> lock(mutex);
    params.wavPath[track] = path;
}

void Controller::setVolume(int track, float vol) {
    std::lock_guard<std::mutex> lock(mutex);
    params.volumes[track] = vol;
}

RhythmBoxParams Controller::getRhythmBoxParams() {
    std::lock_guard<std::mutex> lock(mutex);
    return params;
}

void Controller::setReverse(int track, bool reverse) {
    std::lock_guard<std::mutex> lock(mutex);
    params.reverse[track] = reverse;
}


