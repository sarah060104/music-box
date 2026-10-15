# Music Box

A small C++ step sequencer. Load a WAV sample on each track, activate steps on the grid, and shape the sound with per-track mute, volume and delay.

## Features

- Multiple tracks, each with its own WAV sample
- Step grid: activate or deactivate a step on each track
- Per-track mute
- Per-track volume control
- Delay effect

## Build

Requirements: a C++17 compiler (e.g. `g++` or `clang++`) [+ any library you use, e.g. SFML, PortAudio, miniaudio].

```bash
[g++ -std=c++17 *.cpp -o musicbox]
```

## Run

```bash
./musicbox [path/to/samples]
```

[Explain briefly how to use it: keys, commands, or mouse controls.]

## Demo

[Add a GIF or screenshot here.]

## Project structure

[Optional: list the main files, e.g. `main.cpp`, `track.cpp`, `delay.cpp`.]
