#pragma once

#include <string>
#include "flixel/FlxState.h"
#include "flixel/FlxSprite.h"
#include "flixel/text/FlxText.h"
#include "flixel/sound/FlxSound.h"

class SplashState : public flixel::FlxState {
public:
    SplashState() = default;
    ~SplashState() override = default;

    void create() override;
    void update(float elapsed) override;
    void draw() override;
    void destroy() override;

private:
    flixel::FlxSprite* logo = nullptr;
    flixel::FlxText* welcomeText = nullptr;
    flixel::FlxText* funnyText = nullptr;
    float timer = 0.0f;
    bool hasShownFunnyText = false;
    std::vector<std::string> introTexts = {
        "Look Ma, I'm in a video game!",
        "Swag Swag Cool Shit",
        "I love ninjamuffin99",
        "Follow yophlox on twitter!",
        "Inspired by FNF and OSU!Mania",
        "The first o in the Moon 4k logo stole government files, das why it's hidden lol!"
    };
};