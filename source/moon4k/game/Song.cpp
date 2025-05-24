#include "Song.h"
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Song::Song(const std::string& song, 
           const std::vector<SwagSection>& notes, 
           float bpm, 
           int sections, 
           int keyCount, 
           const std::array<int, 2>& timescale)
    : song(song)
    , notes(notes)
    , bpm(bpm)
    , sections(sections)
    , keyCount(keyCount)
    , timescale(timescale)
    , speed(1.0f)
{
    sectionLengths = notes;
}

SwagSong Song::loadFromJson(const std::string& jsonInput, const std::string& folder) {
    std::string path = "assets/charts/" + folder + "/" + jsonInput + ".moon";
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open Moon4K chart file: " + path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string rawJson = buffer.str();

    while (!rawJson.empty() && rawJson.back() != '}') {
        rawJson.pop_back();
    }

    json j = json::parse(rawJson);
    SwagSong swagSong;

    const auto& songData = j["song"];
    swagSong.song = songData["song"];
    swagSong.bpm = songData["bpm"];
    swagSong.sections = songData["sections"];
    swagSong.speed = songData.value("speed", 1.0f);
    swagSong.keyCount = songData.value("keyCount", 4);
    
    if (songData.contains("timescale")) {
        const auto& ts = songData["timescale"];
        swagSong.timescale = {ts[0], ts[1]};
    } else {
        swagSong.timescale = {4, 4};
    }

    const auto& notesArray = songData["notes"];
    for (const auto& note : notesArray) {
        SwagSection section;
        section.bpm = note.value("bpm", swagSong.bpm);
        section.changeBPM = note.value("changeBPM", false);
        
        if (note.contains("timeScale")) {
            const auto& ts = note["timeScale"];
            section.timeScale = {ts[0], ts[1]};
        } else {
            section.timeScale = swagSong.timescale;
        }
        section.changeTimeScale = note.value("changeTimeScale", false);

        const auto& sectionNotes = note["sectionNotes"];
        for (const auto& sn : sectionNotes) {
            SwagNote swagNote;
            swagNote.noteStrum = sn[0];
            swagNote.noteData = sn[1];
            swagNote.noteSus = sn[2];
            section.sectionNotes.push_back(swagNote);
        }

        swagSong.notes.push_back(section);
    }

    swagSong.sectionLengths = swagSong.notes;

    return swagSong;
}
