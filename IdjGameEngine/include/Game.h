#pragma once
#include "State.h"

class Game {
public:
    ~Game();

    static Game& GetInstance();
    SDL_Renderer* GetRenderer() const;
    State* GetCurrentState() const;

    void Push(State* state);

    void Run();

    float GetDeltaTime() const;

private:
    Game(const std::string& title, int width, int height);
    void CalculateDeltaTime();

    static Game* instance;
    State* storedState;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::stack<std::unique_ptr<State>> stateStack;

    unsigned frameStart;
    float dt;
};
