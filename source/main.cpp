#include "flixel/FlxGame.h"
#include "moon4k/states/SplashState.h"
#include "imports.h"

struct MainConfig {
    int width = 1280;        // Width of the game in pixels
    int height = 720;        // Height of the game in pixels
    int framerate = 60;      // How many frames per second the game should run at
    bool skipSplash = false; // Whether to skip the splash screen (DOES NOTHING AS OF RN LOL)
    bool startFullscreen = false; // Whether to start in fullscreen
    std::string title = "Moon4K - NeoFlixel"; // Window title
};

int main(int argc, char* argv[]) {
    MainConfig config;

    try {
        flixel::FlxGame game(
            config.width,
            config.height,
            config.framerate,
            config.framerate,
            config.title
        );

        game.switchState(new SplashState());

        if (config.startFullscreen) {
            game.setFullscreen(true);
        }

        game.run();
    }
    catch (const std::exception& e) {
        SDL_Log("Error: %s", e.what());
        return 1;
    }

    return 0;
}
