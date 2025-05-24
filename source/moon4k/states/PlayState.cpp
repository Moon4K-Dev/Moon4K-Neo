#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "PlayState.h"
#include "flixel/FlxG.h"

PlayState::PlayState(const std::string& name)
    : name(name)
{
}

void PlayState::create() {
    std::cout << "PlayState: Create Function Called!" << std::endl;
    
    try {
        loadSong();
    } catch (const std::exception& e) {
        std::cerr << "Failed to load song: " << e.what() << std::endl;
        return;
    }
    
    conductor = new Conductor();
    conductor->setBPM(song.bpm);
    conductor->setSpeed(songSpeed);
    add(conductor);
    
    positionText = new flixel::FlxText(0, 0, 300, "Moon4K NeoFlixel port is in development (trust)", 16);
    positionText->setFont("assets/fonts/monsterrat.ttf");
    positionText->setColor(0xFFFFFFFF);
    positionText->setBorderStyle(flixel::FlxTextBorderStyle::SHADOW, {0, 0, 0, 255}, 2.0f);
    positionText->setAlignment(flixel::FlxTextAlign::CENTER);
    positionText->setWordWrap(true);
    positionText->updateHitbox();
    positionText->screenCenter();
    add(positionText);

    startSong();
}

void PlayState::loadSong() {
    std::string chartPath = "assets/charts/" + name + "/" + name + ".moon";
    std::ifstream chartFile(chartPath);
    if (!chartFile.is_open()) {
        throw std::runtime_error("Failed to open chart file: " + chartPath);
    }
    else {
        std::cout << "Loaded chart: " << chartPath << std::endl;
    }

    song.song = name;
    song.bpm = 100.0f;
    songLoaded = true;

    std::string audioPath = "assets/charts/" + name + "/" + name + ".ogg";

    inst = new flixel::FlxSound();
    if (!inst->loadEmbedded(audioPath, false, true)) {
        throw std::runtime_error("Failed to load audio track: " + audioPath);
    }
    add(inst);
}

void PlayState::startSong() {
    if (!songLoaded) return;

    songSpeed = 1.0f;
    if (conductor) {
        conductor->setBPM(song.bpm);
        conductor->setSpeed(songSpeed);
    }

    inst->play(false, 0, 0);

    if (positionText) {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << songSpeed;
        positionText->setText("Now playing: " + song.song + "\nBPM: " + std::to_string(song.bpm) + "\nSpeed: " + ss.str() + "x");
        positionText->screenCenter();
    }
}

void PlayState::update(float elapsed) {
    auto* currentSubState = subState;
    
    FlxState::update(elapsed);
    
    if (currentSubState && !subState) {
        return;
    }
    
    if (!subState) {
        if (flixel::FlxG::keys.justPressed().count(SDL_SCANCODE_RETURN)) {
           // openSubState(new TestSubState());
        }

        if (songLoaded && positionText) {
            float instTime = inst ? inst->get_time() : 0.0f;
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << instTime;
            std::stringstream speedSS;
            speedSS << std::fixed << std::setprecision(1) << songSpeed;
            positionText->setText("Song: " + song.song + "\nTime: " + ss.str() + "s\nSpeed: " + speedSS.str() + "x");
            positionText->screenCenter();
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
    
    if (inst) {
        remove(inst, true);
        inst = nullptr;
    }

    if (conductor) {
        remove(conductor, true);
        conductor = nullptr;
    }
    
    FlxState::destroy();
} 