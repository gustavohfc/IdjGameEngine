﻿#include "pch.h"
#include "Game.h"
#include "Resources.h"
#include "InputManager.h"

Game* Game::instance = nullptr;


Game::Game(const std::string& title, int width, int height):
    frameStart(0),
    dt(0) {

    if (instance != nullptr) {
        throw std::logic_error("Game instance already exists");
    }

    instance = this;

    srand(time(nullptr));

    // Init the SDL
    auto initReturn = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if (initReturn != 0) {
        throw std::runtime_error(SDL_GetError());
    }

    // Init the SDL image
    auto imgFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    auto imgInitReturn = IMG_Init(imgFlags);
    if (imgInitReturn != imgFlags) {
        throw std::runtime_error(IMG_GetError());
    }

    // Init the SDL mixer
    auto mixOpenAudioReturn = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    if (mixOpenAudioReturn != 0) {
        throw std::runtime_error(Mix_GetError());
    }

    auto mixFlags = MIX_INIT_OGG;
    auto mixInitReturn = Mix_Init(mixFlags);
    if (mixInitReturn != mixFlags) {
        throw std::runtime_error(Mix_GetError());
    }

    Mix_AllocateChannels(32);

    // Create the window
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }

    // Create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }

    // Init the game state
    state = new State();
}


Game::~Game() {
    delete state;

    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}


void Game::Run() {
    auto& inputManager = InputManager::GetInstance();

    while (!state->QuitRequested()) {
        CalculateDeltaTime();
        inputManager.Update();
        state->Update(dt);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}


SDL_Renderer* Game::GetRenderer() const {
    return renderer;
}


State& Game::GetState() const {
    return *state;
}


Game& Game::GetInstance() {
    if (instance == nullptr) {
        instance = new Game("Gustavo Henrique Fernandes Carvalho 14/0021671", 1024, 600);
    }
    return *instance;
}


float Game::GetDeltaTime() const {
    return dt;
}


void Game::CalculateDeltaTime() {
    auto currentTime = SDL_GetTicks() / 1000.0;
    dt = currentTime - frameStart;
    frameStart = currentTime;
}
