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
#include "Constants.h"

int Alien::alienCount = 0;


Alien::Alien(GameObject& associated, int nMinions):
	Component(associated),
	state(AlienState::RESTING),
	hp(Constants::Alien::INITIAL_HP),
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
	auto state = Game::GetInstance().GetCurrentState();
	double arc = (2 * M_PI) / nMinions;

	for (int i = 0; i < nMinions; i++) {
		auto minionGO = std::make_shared<GameObject>();
		minionGO->AddComponent(std::make_shared<Minion>(*minionGO, state->GetObjectPtr(&associated), float(arc * i)));
		this->minionArray.push_back(minionGO);
		state->AddObject(minionGO);
	}
}


void Alien::Update(float dt) {
	if (hp <= 0) {
		Die();
		return;
	}

	associated.angleDeg -= Constants::Alien::ROTATION_SPEED * dt;

	if (state == AlienState::MOVING) {
		if (speed.x == 0 && speed.y == 0) {
			speed = Vec2::GetUnitVectorBetweenTwoPoints(associated.box.GetCenter(), destination) * Constants::Alien::LINEAR_SPEED;
		}

		bool arrived = associated.box.Move(speed * dt, destination);

		if (arrived) {
			speed = {0, 0};

			if (auto player = PenguinBody::player) {
				auto playerCenter = player->GetCenter();

				auto minionCompare = [&playerCenter](std::shared_ptr<GameObject> a, std::shared_ptr<GameObject> b) {
					return a->box.Dist(playerCenter) < b->box.Dist(playerCenter);
				};

				auto closestMinion = *std::min_element(minionArray.begin(), minionArray.end(), minionCompare);

				closestMinion->GetComponent<Minion>()->Shoot(playerCenter);

				state = AlienState::RESTING;
				restTimer.Restart();
			}
		}

	} else if (state == AlienState::RESTING) {

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


void Alien::NotifyCollision(GameObject& other) {
	auto bullet = other.GetComponent<Bullet>();

	if (bullet && !bullet->targetsPlayer) {
		hp -= bullet->GetDamage();
	}
}


void Alien::Die() {
	associated.RequestDelete();

	auto state = Game::GetInstance().GetCurrentState();

	auto alienDeath = std::make_shared<GameObject>();
	alienDeath->AddComponent(
		std::make_shared<Sprite>(
			*alienDeath,
			"assets/img/aliendeath.png",
			Constants::Alien::DEATH_FRAME_COUNT,
			Constants::Alien::DEATH_FRAME_TIME,
			Constants::Alien::DEATH_SECONDS_TO_SELF_DESTRUCT
		)
	);

	auto boomSound = std::make_shared<Sound>(*alienDeath, "assets/audio/boom.wav");
	boomSound->Play();
	alienDeath->AddComponent(boomSound);
	alienDeath->box.SetCenter(associated.box.GetCenter());
	state->AddObject(alienDeath);
}
