#include "Controller.h"

#include "AudioFileReader.h"


void Controller::setPlaying(bool playing) {
    params.playing = playing;
}
void Controller::setBpm(int bpm) {
    params.bpm = bpm;

}
void Controller::loadFile(std::string path) {
}

