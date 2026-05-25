# More recent versions of CMake exist.
# Version 3.20 is chosen here to ensure the examples work everywhere.

cmake_minimum_required(VERSION 3.20)

project(beatbox_61601)

# More recent C++ versions of the C++ standard exist.
# Standard C++20 has all the features needed to illustrate the
# core concepts taught in 4DEV, and is widely supported.
set(CMAKE_CXX_STANDARD 20)

add_executable(bbx-61601 main.cpp
        MainWindow.h
        MainWindow.cpp

        AudioGenerator.cpp
        AudioGenerator.h

        libraries/imgui/imgui.cpp
        libraries/imgui/imgui_demo.cpp
        libraries/imgui/imgui_draw.cpp
        libraries/imgui/imgui_widgets.cpp
        libraries/imgui/imgui_tables.cpp
        libraries/imgui/backends/imgui_impl_sdl3.cpp
        libraries/imgui/backends/imgui_impl_sdlrenderer3.cpp
        AudioPlayer.cpp
        AudioPlayer.h
        AudioFileReader.cpp
        AudioFileReader.h
        Controller.cpp
        Controller.h
        RhythmBoxParams.h
        Sequencer.cpp
        Sequencer.h
        Mixer.cpp
        Mixer.h
        Delay.cpp
        Delay.h
)


include_directories( PRIVATE
        "."
)

include_directories(
        "libraries/imgui/backends"
        "libraries/imgui"
        "libraries/portaudio/include"
        "libraries/sdl/include"
)
if (APPLE)
    set(SDL3_FW "${CMAKE_SOURCE_DIR}/libraries/sdl/lib/macos/SDL3.framework")

    target_link_libraries(bbx-61601 PRIVATE
            "${SDL3_FW}/Versions/A/SDL3"
            "-framework AudioToolbox"
            "-framework CoreAudio"
            "-framework Carbon"
            "${CMAKE_SOURCE_DIR}/libraries/portaudio/lib/macos/libportaudio.a")
    target_link_options(bbx-61601 PRIVATE
            "-Wl,-rpath,${CMAKE_SOURCE_DIR}/libraries/sdl/lib/macos")

elseif (WIN32)
    target_link_libraries(bbx-61601 PRIVATE
            "${CMAKE_SOURCE_DIR}/libraries/sdl/lib/win32/sdl3.dll"
            "${CMAKE_SOURCE_DIR}/libraries/portaudio/lib/win32/portaudio_x64.dll"
    )

    add_custom_command(TARGET bbx-61601 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/libraries/sdl/lib/win32/sdl3.dll"
            "$<TARGET_FILE_DIR:bbx-61601>"
    )
    add_custom_command(TARGET bbx-61601 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/libraries/portaudio/lib/win32/portaudio_x64.dll"
            "$<TARGET_FILE_DIR:bbx-61601>"
    )
elseif (UNIX)
    target_link_libraries(bbx-61601 PRIVATE
            "-lGL"
            "-ldl"
            "-ljack"
            "${CMAKE_SOURCE_DIR}/libraries/sdl/lib/linux-x86_64/libSDL3.a"
            "${CMAKE_SOURCE_DIR}/libraries/portaudio/lib/linux-x86_64/libportaudio.a")
endif ()

