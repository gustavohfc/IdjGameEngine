#include "pch.h"
#include "Alien.h"
#include "InputManager.h"


Alien::Alien(GameObject& associated, int nMinions):
    Component(associated) {
    // TODO
}


Alien::~Alien() {
    minionArray.clear(); // TODO: minionArray should be shared_ptr
}


void Alien::Start() {}


void Alien::Update(float dt) {
    auto& inputManager = InputManager::GetInstance();

    if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        taskQueue.emplace(Action::SHOOT, inputManager.GetMouseMapPos());
    }

    if (inputManager.MousePress(RIGHT_MOUSE_BUTTON)) {
        taskQueue.emplace(Action::MOVE, inputManager.GetMouseMapPos());
    }

    if (!taskQueue.empty()) {
        auto task = taskQueue.front();

        if (task.type == Action::MOVE) {
            auto speed = 
        } else {
            //TODO
        }
    }
}


void Alien::Render() {}

bool Alien::Is(const std::string& type) {}


Alien::Action::Action(ActionType type, Vec2 pos): type(type),
                                                  pos(pos) {}
