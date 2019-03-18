#pragma once
#include <string>
#include "SDL.h"
#include "State.h"

class Game {
public:
    ~Game();

    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();

private:
    Game(std::string title, int width, int height);

    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
};
