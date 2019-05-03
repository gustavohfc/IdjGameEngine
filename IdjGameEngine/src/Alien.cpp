#include "pch.h"
#include "Alien.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Minion.h"
#include "Game.h"


Alien::Alien(GameObject& associated, int nMinions):
    Component(associated),
    nMinions(nMinions) {

    auto alienSprite = std::make_shared<Sprite>(associated, "assets/img/alien.png");
    associated.AddComponent(alienSprite);
}


Alien::~Alien() {
    minionArray.clear();
}


void Alien::Start() {
    auto state = Game::GetInstance().GetState();
    double arc = (2 * M_PI) / nMinions;

    for (int i = 0; i < nMinions; i++) {
        auto minionGO = std::make_shared<GameObject>();
        minionGO->AddComponent(std::make_shared<Minion>(*minionGO, state->GetObjectPtr(&associated), arc * i));
        this->minionArray.push_back(minionGO);
        state->AddObject(minionGO);
    }
}


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
            bool arrived = associated.box.Move(dt, 200, task.pos);

            if (arrived) {
                taskQueue.pop();
            }

        } else if (task.type == Action::SHOOT) {
            //TODO
            taskQueue.pop();
        }
    }
}


void Alien::Render() {}


bool Alien::Is(const std::string& type) {
    return type == "Alien";
}


Alien::Action::Action(ActionType type, Vec2 pos): type(type),
                                                  pos(pos) {}
