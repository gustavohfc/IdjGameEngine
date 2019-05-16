#pragma once
#include "Component.h"
#include "Timer.h"


class PenguinCannon : public Component {
public:
	PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);

	void Start() override;
	void Update(float dt) override;
	void Render() override;

	void Shoot();

	ComponentType GetType() const override { return Type; };
	static const ComponentType Type = ComponentType::PenguinCannon;

private:
	std::weak_ptr<GameObject> pbody;
	float angle;

	Timer shootCoolDown;
};
