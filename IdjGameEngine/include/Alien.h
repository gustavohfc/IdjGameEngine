#pragma once
#include "GameObject.h"
#include "Timer.h"


class Alien : public Component {
public:
	Alien(GameObject& associated, int nMinions);
	~Alien();

	void Start() override;
	void Update(float dt) override;
	void Render() override;

	void NotifyCollision(GameObject& other) override;

	ComponentType GetType() const override { return Type; };
	static const ComponentType Type = ComponentType::Alien;

	static int alienCount;

private:
	void Die();

	enum class AlienState { MOVING, RESTING };

	AlienState state;
	Timer restTimer;
	Vec2 destination;

	Vec2 speed = {0, 0};
	int hp;

	int nMinions;
	std::vector<std::shared_ptr<GameObject>> minionArray;
};
