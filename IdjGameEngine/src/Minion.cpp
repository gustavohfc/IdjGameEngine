#include "pch.h"
#include "Minion.h"
#include "Sprite.h"
#include "Game.h"
#include "Bullet.h"
#include "Util.h"
#include "Collider.h"
#include "Constants.h"
#include "GameObject.h"


Minion::Minion(GameObject& associated, const std::weak_ptr<GameObject>& alienCenter, float arcOffset):
	Component(associated),
	alienCenter(alienCenter),
	arc(arcOffset) {

	auto scale = float(1 + ((rand() % 5) + 1) / 10.0);

	associated.AddComponent<Sprite>("assets/img/minion.png");
	associated.GetComponent<Sprite>()->SetScale(scale, scale);

	associated.AddComponent<Collider>();

	Update(0);
}


void Minion::Start() {}


void Minion::Update(float dt) {
	arc += Constants::Minion::ANGULAR_VELOCITY * dt;

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


void Minion::Shoot(Vec2 target) const {
	auto state = Game::GetInstance().GetCurrentState();

	auto position = associated.box.GetCenter();
	auto angle = Vec2::GetVectorBetweenTwoPoints(position, target).Angle();

	auto bulletGO = std::make_shared<GameObject>();

	bulletGO->AddComponent<Bullet>(angle, Constants::Minion::BULLET_SPEED, Constants::Minion::BULLET_DAMAGE,
	                               Constants::Minion::BULLET_MAX_DISTANCE, "assets/img/minionbullet2.png", 3, 1.0f, true);

	bulletGO->box.SetCenter(position.x, position.y);
	bulletGO->angleDeg = Util::RadToDeg(angle);
	state->AddObject(bulletGO);
}
