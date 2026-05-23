
#include "MainWindow.h"

#include <iostream>
#include <thread>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"


MainWindow::MainWindow(Controller& controller)
    : controller(controller) {}

constexpr float FRAMERATE = 60.0f;
constexpr std::chrono::duration<double, std::milli> TARGET_FRAMETIME(1000.0 / FRAMERATE);

void MainWindow::init() {

    // Setup SDL
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        SDL_Log("Error: SDL_Init(): %s\n", SDL_GetError());
        return;
    }
    // Create window with SDL_Renderer graphics context
    Uint32 window_flags = SDL_WINDOW_HIDDEN;
    window = SDL_CreateWindow("", 1200,300 , window_flags);
    if (nullptr == window) {
        SDL_Log("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return;
    }
    renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderVSync(renderer, 1);
    if (nullptr == renderer) {
        SDL_Log("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
        return;
    }
    SDL_SetWindowPosition(
            window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // Setup DearImGui style
    ImGui::StyleColorsDark();
    ImGui::GetStyle().WindowRounding = 0.0f;

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
}

void MainWindow::run() {
    const auto clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool done { false };
    while (!done){
        auto frameStart = std::chrono::high_resolution_clock::now();

        SDL_Event event;
        while (SDL_PollEvent(&event)){
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (SDL_EVENT_QUIT == event.type)
                done = true;
            if ((SDL_EVENT_WINDOW_CLOSE_REQUESTED == event.type)
                && (SDL_GetWindowID(window) == event.window.windowID))
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // all the UI code description
        draw();

        // Rendering
        ImGui::Render();
        SDL_SetRenderDrawColorFloat(renderer,
                                    clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);

        // Calculate time spent and sleep if needed
        auto frameEnd = std::chrono::high_resolution_clock::now();
        auto frameDuration = frameEnd - frameStart;
        if (frameDuration < TARGET_FRAMETIME) {
            std::this_thread::sleep_for(TARGET_FRAMETIME - frameDuration);
        }
    }

    // Cleanup
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void MainWindow::draw()
{
    RhythmBoxParams snapshot = controller.getRhythmBoxParams();

    const float SCREEN_W   = 1200.0f;
    const float SCREEN_H   = 800.0f;
    const float TOP_H      = 40.0f;
    const float TITLE_H   = 20.0f;
    const float CONTENT_H  = SCREEN_H - TOP_H- TITLE_H;
    const float PARAMS_W   = 250.0f;
    const float SEQ_W      = SCREEN_W - PARAMS_W;

    const int NUM_TRACKS = 4;
    const int NUM_STEPS  = 16;
    static bool  steps[NUM_TRACKS][NUM_STEPS] = {};
    static float volumes[NUM_TRACKS]          = {1.0f, 1.0f, 1.0f, 1.0f};
    static bool  mutes[NUM_TRACKS]            = {};
    static bool  reverse  = false;
    static bool  delay    = false;
    static float delayTime = 0.0f;
    static float delayMix  = 0.0f;

    static int selectedTrack = 0;

    bool sampleLoaded = false; //TODO pointeur sample


    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(SCREEN_W, SCREEN_H));
    ImGui::Begin("DrumMachine", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove   );


    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(SCREEN_W, TOP_H));
    ImGui::Begin("BPMBar", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize   |
        ImGuiWindowFlags_NoMove);

    if (ImGui::Button(snapshot.playing ? "Stop" : "Play"))
        controller.setPlaying(!snapshot.playing);
        ImGui::SameLine();
    if (ImGui::Button("-")) controller.setBpm(snapshot.bpm - 1);
        ImGui::SameLine();
    ImGui::Text("BPM : %d", snapshot.bpm);
        ImGui::SameLine();
    if (ImGui::Button("+")) controller.setBpm(snapshot.bpm + 1);


    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(0, TOP_H));
    ImGui::SetNextWindowSize(ImVec2(SEQ_W, CONTENT_H));
    ImGui::Begin("Sequencer", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize   |
        ImGuiWindowFlags_NoMove);



        for (int t = 0; t < NUM_TRACKS; t++)
        {

            ImGui::PushID(t);

            ImGui::PushStyleColor(ImGuiCol_Header,        ImVec4(0.2f, 0.4f, 0.8f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.3f, 0.5f, 0.9f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_HeaderActive,  ImVec4(0.1f, 0.3f, 0.7f, 1.0f));

            char label[32];
            snprintf(label, sizeof(label), "Track %d", t + 1);
            if (ImGui::Selectable(label, selectedTrack == t, 0, ImVec2(70, 36)))
                selectedTrack = t;

            ImGui::PopStyleColor(3);
            ImGui::SameLine();

            for (int s = 0; s < NUM_STEPS; s++)
            {
                ImGui::PushID(s);
                bool active = snapshot.grid[t][s];
                ImGui::PushStyleColor(ImGuiCol_Button, active
                    ? ImVec4(1.0f, 0.85f, 0.0f, 1.0f)
                    : ImVec4(0.3f, 0.3f, 0.3f, 1.0f));

                if (ImGui::Button("##step", ImVec2(36, 36)))
                   controller.setStep(t, s, !active);

                ImGui::PopStyleColor();
                ImGui::SameLine();
                ImGui::PopID();
            }

            ImGui::PushStyleColor(ImGuiCol_FrameBg,    ImVec4(0.2f, 0.4f, 0.8f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.2f, 0.4f, 0.8f, 1.0f));
            ImGui::SetNextItemWidth(60);
            ImGui::SliderFloat("##vol", &volumes[t], 0.0f, 1.0f, "%.3f");
            ImGui::PopStyleColor(2);
            ImGui::SameLine();

            ImGui::PushStyleColor(ImGuiCol_Button, snapshot.muted[t]
                ? ImVec4(0.8f, 0.2f, 0.2f, 1.0f)
                : ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
            if (ImGui::Button("M", ImVec2(24, 36)))
                controller.setMute(t, !snapshot.muted[t]);
                ImGui::PopStyleColor();

            ImGui::PopID();
        }

    ImGui::End();


    ImGui::SetNextWindowPos(ImVec2(SEQ_W, TOP_H));
    ImGui::SetNextWindowSize(ImVec2(PARAMS_W, CONTENT_H));
    ImGui::Begin("TrackParams", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize   |
        ImGuiWindowFlags_NoMove);

        ImGui::Text("Track %d", selectedTrack + 1 );
    if (!pendingFilePath.empty()) {
        controller.registerFileName(pendingTrack, pendingFilePath);
        pendingFilePath.clear();
    }

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.4f, 0.8f, 1.0f));
    (snapshot.wavPath[selectedTrack]=="") ? ImGui::Text("(no sample)"): ImGui::Text(getNameOfFile(snapshot.wavPath[selectedTrack]).c_str());

    if (ImGui::Button("Load sample")) {
        pendingTrack = selectedTrack;
        SDL_DialogFileFilter filter = {"WAV files", "wav"};
        SDL_ShowOpenFileDialog(fileDialogCallback, this, window, nullptr, 0, nullptr, false);

    }
        ImGui::PopStyleColor();

        ImGui::Checkbox("Reverse", &reverse);
        ImGui::Checkbox("Delay",   &delay);

        ImGui::PushStyleColor(ImGuiCol_FrameBg,    ImVec4(0.2f, 0.4f, 0.8f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.2f, 0.4f, 0.8f, 1.0f));
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("Delay time", &delayTime, 0.0f, 1.0f, "%.3f");
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("Delay mix",  &delayMix,  0.0f, 1.0f, "%.3f");
        ImGui::PopStyleColor(2);

    ImGui::End();

    ImGui::End();
}


/**
 * when the user have chosen a file, its path is registered in a variable
 * @param userdata
 * @param filelist
 */
void MainWindow::fileDialogCallback(void* userdata, const char* const* filelist, int filter) {
    auto* self = static_cast<MainWindow*>(userdata);
    if (filelist && filelist[0]) {
        self->pendingFilePath = filelist[0];
    }
}

std::string MainWindow::getNameOfFile(std::string& path) {
    int i = path.find_last_of('/');
    path=path.substr(i+1, path.length());
    return path;
}



