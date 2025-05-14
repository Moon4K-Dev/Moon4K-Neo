#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "PlayState.h"
#include "flixel/FlxG.h"

void PlayState::create() {
    std::cout << "PlayState: Create Function Called!" << std::endl;
    
    positionText = new flixel::FlxText(0, 0, 300, "Moon4K NeoFlixel port is in development (trust)", 16);
    positionText->setFont("assets/fonts/monsterrat.ttf");
    positionText->setColor(0xFFFFFFFF);
    positionText->setBorderStyle(flixel::FlxTextBorderStyle::SHADOW, {0, 0, 0, 255}, 2.0f);
    positionText->setAlignment(flixel::FlxTextAlign::CENTER);
    positionText->setWordWrap(true);
    positionText->updateHitbox();
    positionText->screenCenter();
    add(positionText);
}

void PlayState::update(float elapsed) {
    auto* currentSubState = subState;
    
    FlxState::update(elapsed);
    
    if (currentSubState && !subState) {
        return;
    }
    
    if (!subState) {
        float speed = 200.0f * elapsed;

        if (flixel::FlxG::keys.justPressed().count(SDL_SCANCODE_RETURN)) {
           // openSubState(new TestSubState());
        }
    }
}

void PlayState::draw() {
    FlxState::draw();
}

void PlayState::destroy() {
    if (positionText) {
        remove(positionText, true);
        positionText = nullptr;
    }
    
    FlxState::destroy();
} 