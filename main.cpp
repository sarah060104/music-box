#include <iostream>
#include <MainWindow.h>

#include "AudioGenerator.h"

int main() {

    AudioGenerator audio_generator;
    audio_generator.init();

    MainWindow mainWindow;
    mainWindow.init();
    mainWindow.run();
    return 0;
}

