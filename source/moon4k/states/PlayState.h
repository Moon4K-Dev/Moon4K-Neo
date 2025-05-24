#pragma once

#include <string>
#include "flixel/FlxState.h"
#include "flixel/FlxSprite.h"
#include "flixel/text/FlxText.h"
#include "flixel/sound/FlxSound.h"
#include "../game/Song.h"
#include "../game/Conductor.h"
//#include "../substates/TestSubState.h"

class PlayState : public flixel::FlxState {
public:
    PlayState() = default;
    PlayState(const std::string& name);
    ~PlayState() override = default;

    void create() override;
    void update(float elapsed) override;
    void draw() override;
    void destroy() override;

private:
    void loadSong();
    void startSong();

    flixel::FlxText* positionText = nullptr;
    flixel::FlxSound* inst = nullptr;
    Conductor* conductor = nullptr;

    std::string name;
    SwagSong song;
    bool songLoaded = false;
    float songSpeed = 1.0f;
};