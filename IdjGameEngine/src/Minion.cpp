#include "pch.h"
#include "Minion.h"
#include "Sprite.h"
#include "Game.h"
#include "Bullet.h"
#include "Util.h"
#include "Collider.h"

#define ANGULAR_VELOCITY 0.15707963267 // PI/20


Minion::Minion(GameObject& associated, const std::weak_ptr<GameObject>& alienCenter, double arcOffset):
    Component(associated),
    alienCenter(alienCenter),
    arc(arcOffset) {

    auto scale = 1 + ((rand() % 5) + 1) / 10.0;
    
    auto sprite = std::make_shared<Sprite>(associated, "assets/img/minion.png");
    sprite->SetScale(scale, scale);
    associated.AddComponent(sprite);
    associated.AddComponent(std::make_shared<Collider>(associated));

    Update(0);
}


void Minion::Start() {}

void Minion::Update(float dt) {
    arc += ANGULAR_VELOCITY * dt;

    auto alien = alienCenter.lock();
    if (!alien) {
        associated.RequestDelete();
        return;
    }

    auto position = Vec2(200, 0).GetRotated(arc) + alien->box.GetCenter();
    associated.box.SetCenter(position.x, position.y);
    associated.angleDeg = 360 - Util::RadToDeg(arc);
}

void Minion::Render() {}

bool Minion::Is(const std::string& type) {
    return type == "Minion";
}


void Minion::Shoot(Vec2 target) const {
    auto state = Game::GetInstance().GetState();

    auto position = associated.box.GetCenter();
    auto angle = Vec2::GetVectorBetweenTwoPoints(position, target).Angle();

    auto bulletGO = std::make_shared<GameObject>();
    bulletGO->AddComponent(std::make_shared<Bullet>(*bulletGO, angle, 100, 10, 1000, "assets/img/minionbullet2.png", 3, 1, true));
    bulletGO->box.SetCenter(position.x, position.y);
    bulletGO->angleDeg = Util::RadToDeg(angle);
    state->AddObject(bulletGO);
}
