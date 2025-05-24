#include "Conductor.h"
#include "Song.h"
#include <cmath>

Conductor::Conductor() {
    updateTiming();
    safeZoneOffset = std::floor((safeFrames / 60.0f) * 1000.0f);
}

void Conductor::update(float elapsed) {
    songPosition += elapsed * 1000.0f * speed;
    updateTiming();
}

void Conductor::setBPM(float newBpm) {
    bpm = newBpm;
    updateTiming();
}

void Conductor::setSpeed(float newSpeed) {
    speed = newSpeed;
    updateTiming();
}

void Conductor::updateTiming() {
    crochet = (60.0f / bpm) * 1000.0f;
    stepCrochet = crochet / 4.0f;
}

void Conductor::recalculateStuff(float multi) {
    safeZoneOffset = std::floor((safeFrames / 60.0f) * 1000.0f) * multi;

    crochet = ((60.0f / bpm) * 1000.0f);
    stepCrochet = crochet / timeScale[1];

    stepsPerSection = std::floor((16.0f / timeScale[1]) * timeScale[0]);
}

void Conductor::mapBPMChanges(const SwagSong& song, float songMultiplier) {
    bpmChangeMap.clear();
    timeScaleChangeMap.clear();

    float curBPM = song.bpm;
    std::array<int, 2> curTimeScale = timeScale;
    int totalSteps = 0;
    float totalPos = 0.0f;

    for (const auto& section : song.notes) {
        if (section.changeBPM && section.bpm != curBPM) {
            curBPM = section.bpm;

            BPMChangeEvent event{
                totalSteps,
                totalPos,
                curBPM
            };

            bpmChangeMap.push_back(event);
        }

        if (section.changeTimeScale &&
            (section.timeScale[0] != curTimeScale[0] ||
             section.timeScale[1] != curTimeScale[1])) {
            curTimeScale = section.timeScale;

            TimeScaleChangeEvent event{
                totalSteps,
                totalPos,
                curTimeScale
            };

            timeScaleChangeMap.push_back(event);
        }

        int deltaSteps = std::floor((16.0f / curTimeScale[1]) * curTimeScale[0]);
        totalSteps += deltaSteps;

        totalPos += ((60.0f / curBPM) * 1000.0f / curTimeScale[0]) * deltaSteps;
    }

    recalculateStuff(songMultiplier);
}

void Conductor::changeBPM(float newBpm, float multi) {
    bpm = newBpm;
    recalculateStuff(multi);
}