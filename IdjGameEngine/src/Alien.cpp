#include "pch.h"
#include "Alien.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Game.h"
#include "Minion.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sound.h"
#include "PenguinBody.h"

int Alien::alienCount = 0;


Alien::Alien(GameObject& associated, int nMinions):
    Component(associated),
    state(AlienState::RESTING),
    hp(50),
    nMinions(nMinions) {

    associated.AddComponent(std::make_shared<Sprite>(associated, "assets/img/alien.png"));
    associated.AddComponent(std::make_shared<Collider>(associated));

    alienCount++;
}


Alien::~Alien() {
    minionArray.clear();
    alienCount--;
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
        Die();
        return;
    }

    // Rotate
    associated.angleDeg -= 10 * dt;

    if (state == AlienState::MOVING) {
        if (speed.x == 0 && speed.y == 0) {
            speed = Vec2::GetUnitVectorBetweenTwoPoints(associated.box.GetCenter(), destination) * 200;
        }

        bool arrived = associated.box.Move(speed * dt, destination);

        if (arrived) {
            speed = { 0, 0 };

            if (auto player = PenguinBody::player) {
                auto playerCenter = player->GetCenter();

                auto minionCompare = [&playerCenter](std::shared_ptr<GameObject> a, std::shared_ptr<GameObject> b) {
                    return a->box.Dist(playerCenter) < b->box.Dist(playerCenter);
                };

                auto closestMinion = *std::min_element(minionArray.begin(), minionArray.end(), minionCompare);

                closestMinion->GetMinion()->Shoot(playerCenter);

                state = AlienState::RESTING;
                restTimer.Restart();
            }
        }

    }else if (state == AlienState::RESTING) {
        
        restTimer.Update(dt);

        if (restTimer.Get() > 3) {
            if (auto player = PenguinBody::player) {
                destination = player->GetCenter();
                state = AlienState::MOVING;
            }
        }
    }
}


void Alien::Render() {}


bool Alien::Is(const std::string& type) {
    return type == "Alien";
}


void Alien::NotifyCollision(GameObject& other) {
    auto bullet = other.GetBullet();

    if (bullet) {
        hp -= bullet->GetDamage();
    }
}


void Alien::Die() {
    associated.RequestDelete();

    auto state = Game::GetInstance().GetState();

    auto alienDeath = std::make_shared<GameObject>();
    alienDeath->AddComponent(std::make_shared<Sprite>(*alienDeath, "assets/img/aliendeath.png", 4, 0.1, 0.4));
    auto boomSound = std::make_shared<Sound>(*alienDeath, "assets/audio/boom.wav");
    boomSound->Play();
    alienDeath->AddComponent(boomSound);
    alienDeath->box.SetCenter(associated.box.GetCenter());
    state->AddObject(alienDeath);
}
