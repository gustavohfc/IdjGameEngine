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
#include "Constants.h"


PenguinBody* PenguinBody::player = nullptr;


PenguinBody::PenguinBody(GameObject& associated) :
	Component(associated),
	speed({0, 0}),
	linearSpeed(0),
	angle(0),
	hp(Constants::PenguinBody::INITIAL_HP) {

	associated.AddComponent<Sprite>("assets/img/penguin.png");
	associated.AddComponent<Collider>();

	player = this;
}


PenguinBody::~PenguinBody() {
	player = nullptr;
}


void PenguinBody::Start() {
	auto state = Game::GetInstance().GetCurrentState();

	auto penguinCannonGO = std::make_shared<GameObject>();
	penguinCannonGO->AddComponent<PenguinCannon>(state->GetObjectPtr(&associated));
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
		linearSpeed += Constants::PenguinBody::LINEAR_SPEED_INCREMENT;
	}

	if (inputManager.IsKeyDown(SDLK_s)) {
		linearSpeed -= Constants::PenguinBody::LINEAR_SPEED_INCREMENT;
	}

	if (inputManager.IsKeyDown(SDLK_a)) {
		angularSpeed -= Constants::PenguinBody::ANGULAR_SPEED;
	}

	if (inputManager.IsKeyDown(SDLK_d)) {
		angularSpeed += Constants::PenguinBody::ANGULAR_SPEED;
	}

	angle += angularSpeed * dt;
	associated.angleDeg = Util::RadToDeg(angle);

	if (linearSpeed > Constants::PenguinBody::MAX_LINEAR_SPEED) {
		linearSpeed = Constants::PenguinBody::MAX_LINEAR_SPEED;
	} else if (linearSpeed < - Constants::PenguinBody::MAX_LINEAR_SPEED) {
		linearSpeed = - Constants::PenguinBody::MAX_LINEAR_SPEED;
	}

	auto nextPos = associated.box.GetCenter() + Vec2(linearSpeed * dt, 0).GetRotated(angle);
	associated.box.SetCenter(nextPos);
}


void PenguinBody::Render() {}


void PenguinBody::NotifyCollision(GameObject& other) {
	auto bullet = other.GetComponent<Bullet>();

	if (bullet && bullet->targetsPlayer) {
		hp -= bullet->GetDamage();
	}
}


Vec2 PenguinBody::GetCenter() {
	return associated.box.GetCenter();
}


void PenguinBody::Die() {
	associated.RequestDelete();
	Camera::Unfollow();

	auto state = Game::GetInstance().GetCurrentState();

	auto penguinDeath = std::make_shared<GameObject>();
	penguinDeath->AddComponent<Sprite>(
		"assets/img/penguindeath.png",
		Constants::PenguinBody::DEATH_FRAME_COUNT,
		Constants::PenguinBody::DEATH_FRAME_TIME,
		Constants::PenguinBody::DEATH_SECONDS_TO_SELF_DESTRUCT
	);

	auto sound = penguinDeath->AddComponent<Sound>("assets/audio/boom.wav");
	sound->Play();

	penguinDeath->box.SetCenter(associated.box.GetCenter());
	state->AddObject(penguinDeath);
}
