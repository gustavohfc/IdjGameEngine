#include "Game.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

Game* Game::instance = nullptr;

Game::Game(std::string title, int width, int height) {
    if (instance != nullptr) {
        throw std::exception("Game instance already exists");
    }

    instance = this;

    // Init the SDL
    auto initReturn = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if (initReturn != 0) {
        throw std::exception(SDL_GetError());
    }

    // Init the SDL image
    auto imgFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    auto imgInitReturn = IMG_Init(imgFlags);
    if (imgInitReturn != imgFlags) {
        throw std::exception(IMG_GetError());
    }

    // Init the SDL mixer
    auto mixFlags = MIX_INIT_OGG;
    auto mixInitReturn = Mix_Init(mixFlags);
    if (mixInitReturn != mixFlags) {
        throw std::exception(Mix_GetError());
    }

    auto mixOpenAudioReturn = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    if (mixOpenAudioReturn != 0) {
        throw std::exception(Mix_GetError());
    }

    Mix_AllocateChannels(32);

    // Create the window
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr) {
        throw std::exception(SDL_GetError());
    }

    // Create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        throw std::exception(SDL_GetError());
    }

    // Init the game state
    state = new State();
}


Game::~Game() {
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    delete state;
}


void Game::Run() {
    while (!state->QuitRequested()) {
        state->Update(0);
        state->Render();
        SDL_Delay(33);
    }
}


SDL_Renderer* Game::GetRenderer() {
    return renderer;
}


State& Game::GetState() {
    return *state;
}


Game& Game::GetInstance() {
    if (instance == nullptr) {
        instance = new Game("Gustavo Henrique Fernandes Carvalho 14/0021671", 1024, 600);
    }
    return *instance;
}
