#pragma once
#include "Component.h"

class CameraFollower : public Component {
public:
	CameraFollower(GameObject& associated);

	void Start() override;
	void Update(float dt) override;
	void Render() override;

	ComponentType GetType() const override { return Type; };
	static const ComponentType Type = ComponentType::CameraFollower;
};
