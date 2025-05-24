#pragma once

#include <string>
#include <vector>
#include <array>
#include "flixel/FlxBasic.h"
#include "Song.h"

struct BPMChangeEvent {
    int stepTime;
    float songTime;
    float bpm;
};

struct TimeScaleChangeEvent {
    int stepTime;
    float songTime;
    std::array<int, 2> timeScale;
};

class Conductor : public flixel::FlxBasic {
public:
    Conductor();
    ~Conductor() override = default;

    void update(float elapsed) override;

    void setBPM(float bpm);
    void setSpeed(float speed);
    float getBPM() const { return bpm; }
    float getSpeed() const { return speed; }
    float getCrochet() const { return crochet; }
    float getStepCrochet() const { return stepCrochet; }
    float getSongPosition() const { return songPosition; }
    float getLastSongPos() const { return lastSongPos; }
    float getOffset() const { return offset; }
    float getSafeZoneOffset() const { return safeZoneOffset; }
    int getStepsPerSection() const { return stepsPerSection; }
    const std::array<int, 2>& getTimeScale() const { return timeScale; }

    void recalculateStuff(float multi = 1.0f);
    void mapBPMChanges(const SwagSong& song, float songMultiplier = 1.0f);
    void changeBPM(float newBpm, float multi = 1.0f);

private:
    float bpm = 100.0f;
    float speed = 1.0f;
    float crochet = 0.0f;
    float stepCrochet = 0.0f;
    float songPosition = 0.0f;
    float lastSongPos = 0.0f;
    float offset = 0.0f;
    float safeZoneOffset = 0.0f;
    int safeFrames = 10;
    int stepsPerSection = 16;
    std::array<int, 2> timeScale = {4, 4};

    std::vector<BPMChangeEvent> bpmChangeMap;
    std::vector<TimeScaleChangeEvent> timeScaleChangeMap;

    void updateTiming();
};