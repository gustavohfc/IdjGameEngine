#pragma once
#include "Component.h"

class Bullet : public Component {
public:
	Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, const std::string& sprite, int frameCount,
	       float frameTime, bool targetsPlayer);

	void Start() override;
	void Update(float dt) override;
	void Render() override;
	void NotifyCollision(GameObject& other) override;

	int GetDamage() const;

	ComponentType GetType() const override { return Type; };
	static const ComponentType Type = ComponentType::Bullet;

	bool targetsPlayer;

private:
	Vec2 speed;
	float distanceLeft;
	int damage;
};
