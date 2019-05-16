#include "pch.h"
#include "PenguinCannon.h"
#include "Sprite.h"
#include "Util.h"
#include "InputManager.h"
#include "Game.h"
#include "Bullet.h"
#include "Collider.h"
#include "Constants.h"
#include "GameObject.h"


PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody):
	Component(associated),
	pbody(penguinBody),
	angle(0) {

	associated.AddComponent(std::make_shared<Sprite>(associated, "assets/img/cubngun.png"));
	associated.AddComponent(std::make_shared<Collider>(associated));
}


void PenguinCannon::Start() {}


void PenguinCannon::Update(float dt) {
	auto pbody = this->pbody.lock();
	if (!pbody) {
		associated.RequestDelete();
		return;
	}

	auto& inputManager = InputManager::GetInstance();

	angle = Vec2::GetVectorBetweenTwoPoints(associated.box.GetCenter(), inputManager.GetMouseMapPos()).Angle();

	associated.box.SetCenter(pbody->box.GetCenter());
	associated.angleDeg = Util::RadToDeg(angle);

	shootCoolDown.Update(dt);

	if (inputManager.MousePress(LEFT_MOUSE_BUTTON) && shootCoolDown.Get() >= Constants::PenguinCannon::COOLDOWN_TIME) {
		Shoot();
		shootCoolDown.Restart();
	}
}


void PenguinCannon::Render() {}


void PenguinCannon::Shoot() {
	auto state = Game::GetInstance().GetCurrentState();

	auto cannonCenter = associated.box.GetCenter();
	auto cannonTip = cannonCenter + Vec2(associated.box.w / 2, 0).GetRotated(angle);

	auto bulletGO = std::make_shared<GameObject>();

	bulletGO->AddComponent(std::make_shared<Bullet>(*bulletGO, angle, Constants::PenguinCannon::BULLET_SPEED,
	                                                Constants::PenguinCannon::BULLET_DAMAGE, Constants::PenguinCannon::BULLET_MAX_DISTANCE,
	                                                "assets/img/minionbullet2.png", Constants::Bullet::FRAME_COUNT,
	                                                Constants::Bullet::FRAME_TIME, false));

	bulletGO->box.SetCenter(cannonTip.x, cannonTip.y);
	bulletGO->angleDeg = Util::RadToDeg(angle);
	state->AddObject(bulletGO);
}
