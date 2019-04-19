#pragma once
#include "State.h"

class Game {
public:
    ~Game();

    void Run();
    SDL_Renderer* GetRenderer() const;
    State& GetState() const;
    static Game& GetInstance();
    float GetDeltaTime() const;

private:
    Game(const std::string& title, int width, int height);
    void CalculateDeltaTime();

    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

    unsigned frameStart;
    float dt;
};
