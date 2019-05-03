#include "pch.h"
#include "Minion.h"
#include "Sprite.h"
#include "Game.h"
#include "Bullet.h"

#define ANGULAR_VELOCITY 0.15707963267 // PI/20


Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffset):
    Component(associated),
    alienCenter(alienCenter),
    arc(arcOffset) {
    
    auto sprite = std::make_shared<Sprite>(associated, "assets/img/minion.png");
    associated.AddComponent(sprite);

    Update(0);
}


void Minion::Start() {}

void Minion::Update(float dt) {
    arc = arc + ANGULAR_VELOCITY * dt;
    auto center = alienCenter.lock(); // TODO
    auto position = Vec2(150, 0).GetRotated(arc) + center->box.GetCenter();
    associated.box.SetCenter(position.x, position.y);
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
    bulletGO->AddComponent(std::make_shared<Bullet>(*bulletGO, angle, 100, 10, 1000, "assets/img/minionbullet1.png"));
    bulletGO->box.SetCenter(position.x, position.y);
    state->AddObject(bulletGO);
}
