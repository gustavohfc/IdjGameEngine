#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Game.h"


int main(int argc, char** argv) {
    
    Game game = Game::GetInstance();
    game.Run();

    return 0;
}
