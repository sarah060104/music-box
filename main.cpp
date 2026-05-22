#include <iostream>
#include <MainWindow.h>

#include "AudioGenerator.h"

int main() {

    AudioGenerator audioGenerator;
    audioGenerator.players[0].loadWav("../../samplepack/Hihat1.wav");
    audioGenerator.init();

    audioGenerator.players[0].trigger();

    MainWindow mainWindow;
    mainWindow.init();
    mainWindow.run();
    return 0;
}

