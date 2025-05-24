// Basic reimplementation of the og splash
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <random>
#include "SplashState.h"
#include "PlayState.h"
#include "flixel/FlxG.h"
#include "flixel/FlxGame.h"

void SplashState::create() {
    std::cout << "SplashState: Create Function Called!" << std::endl;
    
    welcomeText = new flixel::FlxText(0, 0, 300, "Welcome to Moon4K!", 24);
    welcomeText->setFont("assets/fonts/vcr.ttf");
    welcomeText->setColor(0xFFFFFFFF);
    welcomeText->setAlignment(flixel::FlxTextAlign::CENTER);
    welcomeText->screenCenter();
    welcomeText->y += 35;
    add(welcomeText);

    logo = new flixel::FlxSprite();
    logo->loadGraphic("assets/images/splash/notelogo.png");
    logo->setScale(0.3f);
    logo->updateHitbox();
    logo->x = welcomeText->x;
    logo->y = welcomeText->y - 277;
    add(logo);
    
    funnyText = new flixel::FlxText(0, 0, 300, "", 24);
    funnyText->setFont("assets/fonts/vcr.ttf");
    funnyText->setColor(0xFFFFFFFF);
    funnyText->setAlignment(flixel::FlxTextAlign::CENTER);
    funnyText->screenCenter();
    funnyText->y += 35;
    funnyText->alpha = 0;
    add(funnyText);
    
    timer = 0.0f;
    hasShownFunnyText = false;
}

void SplashState::update(float elapsed) {
    FlxState::update(elapsed);
    
    timer += elapsed;
    
    if (!hasShownFunnyText && timer >= 2.0f) {
        hasShownFunnyText = true;
        welcomeText->alpha = 0;
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, static_cast<int>(introTexts.size() - 1));
        funnyText->setText(introTexts[dis(gen)]);
        funnyText->alpha = 1;
    }
    
    if (timer >= 5.5f) {
        if (flixel::FlxG::game) {
            flixel::FlxG::game->switchState(new PlayState("cheatreal"));
        }
    }
}

void SplashState::draw() {
    FlxState::draw();
}

void SplashState::destroy() {
    if (logo) {
        remove(logo, true);
        logo = nullptr;
    }
    if (welcomeText) {
        remove(welcomeText, true);
        welcomeText = nullptr;
    }
    if (funnyText) {
        remove(funnyText, true);
        funnyText = nullptr;
    }
    
    FlxState::destroy();
} 