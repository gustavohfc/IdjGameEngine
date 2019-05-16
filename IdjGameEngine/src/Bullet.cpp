#include "pch.h"
#include "Alien.h"
#include "Bullet.h"
#include "Sprite.h"
#include "Collider.h"
#include "PenguinBody.h"


Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance,
               const std::string& sprite, int frameCount, float frameTime, bool targetsPlayer):
	Component(associated),
	targetsPlayer(targetsPlayer),
	distanceLeft(maxDistance),
	damage(damage) {

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


void Bullet::NotifyCollision(GameObject& other) {
	if (targetsPlayer && other.GetComponent<PenguinBody>()) {
		associated.RequestDelete();
	}

	if (!targetsPlayer && other.GetComponent<Alien>()) {
		associated.RequestDelete();
	}
}


int Bullet::GetDamage() const {
	return damage;
}


ComponentType Bullet::GetType() const {
	return Type;
}
