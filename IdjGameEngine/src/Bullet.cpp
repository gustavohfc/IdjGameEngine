#include "pch.h"
#include "Bullet.h"
#include "Sprite.h"
#include "Collider.h"


Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance,
               const std::string& sprite, int frameCount, float frameTime, bool targetsPlayer):
    Component(associated),
    distanceLeft(maxDistance),
    damage(damage),
    targetsPlayer(targetsPlayer) {

    this->speed = Vec2(speed * cos(angle), speed * sin(angle));

    associated.AddComponent(std::make_shared<Sprite>(associated, sprite, frameCount, frameTime));
    associated.AddComponent(std::make_shared<Collider>(associated));
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


void Bullet::NotifyCollision(GameObject& other) {
    if (targetsPlayer && other.GetPenguinBody()) {
        associated.RequestDelete();
    }

    if (other.GetAlien()) {
        associated.RequestDelete();
    }
}


int Bullet::GetDamage() const {
    return damage;
}
