#include <iostream>
#include <MainWindow.h>

#include "AudioGenerator.h"
#include "Controller.h"
#include "Preferences.h"

int main() {

    Controller controller;

    AudioGenerator audioGenerator(controller);
    audioGenerator.init();

    MainWindow mainWindow(controller);
    mainWindow.init();


    std::array<std::string, 4> savedPaths = Preferences::load();
    for (int t = 0; t < 4; t++)
        if (!savedPaths[t].empty())
            controller.registerFileName(t, savedPaths[t]);

    mainWindow.run();

    return 0;
}

