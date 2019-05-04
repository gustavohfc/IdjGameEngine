#include "pch.h"
#include "PenguinBody.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Util.h"
#include "Collider.h"
#include "Game.h"
#include "PenguinCannon.h"
#include "Bullet.h"
#include "Camera.h"
#include "Sound.h"


PenguinBody* PenguinBody::player = nullptr;


PenguinBody::PenguinBody(GameObject& associated) :
    Component(associated),
    speed({0, 0}),
    linearSpeed(0),
    angle(0),
    hp(40) {

    associated.AddComponent(std::make_shared<Sprite>(associated, "assets/img/penguin.png"));
    associated.AddComponent(std::make_shared<Collider>(associated));

    player = this;
}


PenguinBody::~PenguinBody() {
    player = nullptr;
}


void PenguinBody::Start() {
    auto state = Game::GetInstance().GetState();

    auto penguinCannonGO = std::make_shared<GameObject>();
    penguinCannonGO->AddComponent(std::make_shared<PenguinCannon>(*penguinCannonGO, state->GetObjectPtr(&associated)));
    state->AddObject(penguinCannonGO);

    pcannon = penguinCannonGO;
}


void PenguinBody::Update(float dt) {
    if (hp <= 0) {
        Die();
        return;
    }

    auto& inputManager = InputManager::GetInstance();

    float angularSpeed = 0;

    if (inputManager.IsKeyDown(SDLK_w)) {
        linearSpeed += 5;
    }

    if (inputManager.IsKeyDown(SDLK_s)) {
        linearSpeed -= 5;
    }

    if (inputManager.IsKeyDown(SDLK_a)) {
        angularSpeed -= 1;
    }

    if (inputManager.IsKeyDown(SDLK_d)) {
        angularSpeed += 1;
    }

    angle += angularSpeed * dt;
    associated.angleDeg = Util::RadToDeg(angle);

    if (linearSpeed > 100) {
        linearSpeed = 100;
    } else if (linearSpeed < -100) {
        linearSpeed = -100;
    }

    auto nextPos = associated.box.GetCenter() + Vec2(linearSpeed * dt, 0).GetRotated(angle);
    associated.box.SetCenter(nextPos);
}


void PenguinBody::Render() {}


bool PenguinBody::Is(const std::string& type) {
    return type == "PenguinBody";
}


void PenguinBody::NotifyCollision(GameObject& other) {
    auto bullet = other.GetBullet();

    if (bullet && bullet->targetsPlayer) {
        hp -= bullet->GetDamage();
    }
}


void PenguinBody::Die() {
    associated.RequestDelete();
    Camera::Unfollow();

    auto state = Game::GetInstance().GetState();

    auto penguinDeath = std::make_shared<GameObject>();
    penguinDeath->AddComponent(std::make_shared<Sprite>(*penguinDeath, "assets/img/penguindeath.png", 5, 0.1, 0.5));
    auto boomSound = std::make_shared<Sound>(*penguinDeath, "assets/audio/boom.wav");
    boomSound->Play();
    penguinDeath->AddComponent(boomSound);
    penguinDeath->box.SetCenter(associated.box.GetCenter());
    state->AddObject(penguinDeath);
}
