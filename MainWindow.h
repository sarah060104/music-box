
#ifndef TESTINSTRUCT_MAINWINDOW_H
#define TESTINSTRUCT_MAINWINDOW_H

#include <SDL3/SDL.h>

#include "Controller.h"

class MainWindow {
public :
    MainWindow(Controller& controller);
    void init();
    void run();
private:
    void draw();
    SDL_Window* window { nullptr };
    SDL_Renderer* renderer { nullptr };
    Controller& controller;

    static void fileDialogCallback(void* userdata, const char* const* filelist, int filter);

    std::string getNameOfFile(std::string &path);

    std::string pendingFilePath;
    int pendingTrack = 0;

};

#endif //TESTINSTRUCT_MAINWINDOW_H
