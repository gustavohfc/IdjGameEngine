#include "pch.h"
#include "Bullet.h"
#include "Sprite.h"


Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance,
               const std::string& sprite):
    Component(associated),
    distanceLeft(maxDistance),
    damage(damage) {

    this->speed = Vec2(speed * cos(angle), speed * sin(angle));

    auto spriteCmp = std::make_shared<Sprite>(associated, sprite);
    associated.AddComponent(spriteCmp);
}


void Bullet::Start() {}


void Bullet::Update(float dt) {
    auto currentCenter = associated.box.GetCenter();
    auto nextCenter = currentCenter + speed * dt;

    associated.box.SetCenter(nextCenter.x, nextCenter.y);

    distanceLeft -= currentCenter.Dist(nextCenter);

    if (distanceLeft < 0) {
        associated.RequestDelete();
    }
}


void Bullet::Render() {}


bool Bullet::Is(const std::string& type) {
    return type == "Bullet";
}


int Bullet::GetDamage() const {
    return damage;
}
