#include "pch.h"
#include "InputManager.h"


void InputManager::Update() {
    static auto controller = SDL_GameControllerOpen(0);

    axisX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
    axisY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);

    quitRequested = false;

    SDL_GetMouseState(&mouseX, &mouseY);

    updateCounter++;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (!event.key.repeat) {
            if (event.type == SDL_QUIT) {

                quitRequested = true;

            } else if (event.type == SDL_KEYDOWN) {

                keyState[event.key.keysym.sym] = true;
                keyUpdate[event.key.keysym.sym] = updateCounter;

            } else if (event.type == SDL_KEYUP) {

                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;

            } else if (event.type == SDL_MOUSEBUTTONDOWN) {

                mouseState[event.button.button] = true;
                mouseUpdate[event.button.button] = updateCounter;

            } else if (event.type == SDL_MOUSEBUTTONUP) {

                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;

            }
        }
    }
}


bool InputManager::KeyPress(int key) {
    return keyState[key] && keyUpdate[key] == updateCounter;
}


bool InputManager::KeyRelease(int key) {
    return !keyState[key] && keyUpdate[key] == updateCounter;
}


bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}


bool InputManager::MousePress(int button) {
    return mouseState[button] && mouseUpdate[button] == updateCounter;
}


bool InputManager::MouseRelease(int button) {
    return !mouseState[button] && mouseUpdate[button] == updateCounter;
}


bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}


int InputManager::GetMouseX() const {
    return mouseX;
}


int InputManager::GetMouseY() const {
    return mouseY;
}


bool InputManager::QuitRequested() const {
    return quitRequested;
}


InputManager& InputManager::GetInstance() {
    static InputManager inputManager;
    return inputManager;
}


InputManager::InputManager():
    mouseState{},
    mouseUpdate{},
    quitRequested(false),
    updateCounter(0),
    mouseX(0),
    mouseY(0) {}


InputManager::~InputManager() {}
