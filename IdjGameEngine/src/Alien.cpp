#include "pch.h"
#include "Alien.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Game.h"
#include "Minion.h"


Alien::Alien(GameObject& associated, int nMinions):
    Component(associated),
    nMinions(nMinions),
    hp(50) {

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
    if (hp <= 0) {
        associated.RequestDelete();
        return;
    }

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
            if (speed.x == 0 && speed.y == 0) {
                speed = Vec2::GetUnitVectorBetweenTwoPoints(associated.box.GetCenter(), task.pos) * 200;
            }

            bool arrived = associated.box.Move(speed * dt, task.pos);

            if (arrived) {
                speed = {0, 0};
                taskQueue.pop();
            }

        } else if (task.type == Action::SHOOT) {
            auto minionCompare = [&task](std::shared_ptr<GameObject> a, std::shared_ptr<GameObject> b) {
                return a->box.Dist(task.pos) < b->box.Dist(task.pos);
            };

            auto closestMinion = *std::min_element(minionArray.begin(), minionArray.end(), minionCompare);

            closestMinion->GetMinion()->Shoot(task.pos);

            taskQueue.pop();
        }
    }

    // Rotate
    associated.angleDeg += 10 * dt;
}


void Alien::Render() {}


bool Alien::Is(const std::string& type) {
    return type == "Alien";
}


Alien::Action::Action(ActionType type, Vec2 pos):
    type(type),
    pos(pos) {}
