#include <iostream>
#include <MainWindow.h>

#include "AudioGenerator.h"
#include "Controller.h"

int main() {

    Controller controller;

    AudioGenerator audioGenerator(controller);
    audioGenerator.init();

    MainWindow mainWindow(controller);
    mainWindow.init();
    mainWindow.run();

    return 0;
}

