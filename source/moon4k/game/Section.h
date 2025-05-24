#pragma once

#include <vector>
#include <array>

struct SwagNote {
    float noteStrum;
    int noteData;
    float noteSus;
};

struct SwagSection {
    std::vector<SwagNote> sectionNotes;
    float bpm;
    bool changeBPM;

    std::array<int, 2> timeScale;
    bool changeTimeScale;
};
