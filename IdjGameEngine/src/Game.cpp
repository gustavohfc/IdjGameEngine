#include "pch.h"
#include "Game.h"
#include "InputManager.h"
#include "Constants.h"

Game* Game::instance = nullptr;


Game::Game(const std::string& title, int width, int height):
	frameStart(0),
	dt(0) {

	if (instance != nullptr) {
		throw std::logic_error("Game instance already exists");
	}

	instance = this;

	srand(int(time(nullptr)));

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

	storedState = nullptr;
}


Game::~Game() {
	delete storedState;

	while (!stateStack.empty()) {
		stateStack.pop();
	}

	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}


void Game::Run() {
	if (storedState == nullptr) {
		return;
	}

	auto& inputManager = InputManager::GetInstance();

	stateStack.emplace(storedState);
	storedState = nullptr;

	stateStack.top()->Start();

	while (!stateStack.empty() && !stateStack.top()->QuitRequested()) {

		if (stateStack.top()->PopRequested()) {
			stateStack.pop();

			if (!stateStack.empty() && storedState == nullptr) {
				stateStack.top()->Resume();
			}
		}

		if (storedState != nullptr) {
			stateStack.top()->Pause();
			stateStack.emplace(storedState);
			stateStack.top()->Start();
			storedState = nullptr;
		}

		if (stateStack.empty()) {
			break;
		}

		CalculateDeltaTime();
		inputManager.Update();

		stateStack.top()->Update(dt);
		stateStack.top()->Render();

		SDL_RenderPresent(renderer);
		SDL_Delay(Constants::Game::SDL_DELAY);
	}
}


SDL_Renderer* Game::GetRenderer() const {
	return renderer;
}


State* Game::GetCurrentState() const {
	return stateStack.top().get();
}


void Game::Push(State* state) {
	storedState = state;
}


Game& Game::GetInstance() {
	if (instance == nullptr) {
		instance = new Game(Constants::Game::WINDOW_TITLE, Constants::Game::WINDOW_WIDTH, Constants::Game::WINDOW_HEIGHT);
	}
	return *instance;
}


float Game::GetDeltaTime() const {
	return dt;
}


void Game::CalculateDeltaTime() {
	auto currentTime = SDL_GetTicks();
	dt = float((currentTime - frameStart) / 1000.0);
	frameStart = currentTime;
}
