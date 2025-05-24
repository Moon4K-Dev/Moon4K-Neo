#pragma once

#include <string>
#include <vector>
#include <array>
#include <memory>
#include "Section.h"

struct SwagSong {
    std::string song;
    std::vector<SwagSection> notes;
    float bpm;
    int sections;
    std::vector<SwagSection> sectionLengths;
    float speed;
    int keyCount;
    std::array<int, 2> timescale;
};

class Song {
public:
    std::string song;
    std::vector<SwagSection> notes;
    float bpm;
    int sections;
    std::vector<SwagSection> sectionLengths;
    float speed;
    int keyCount;
    std::array<int, 2> timescale;

    Song(const std::string& song, 
         const std::vector<SwagSection>& notes, 
         float bpm, 
         int sections, 
         int keyCount, 
         const std::array<int, 2>& timescale = {4, 4});

    static SwagSong loadFromJson(const std::string& jsonInput, const std::string& folder = "");
};
