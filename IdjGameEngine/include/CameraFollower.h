#pragma once
#include "Component.h"

class CameraFollower : public Component {
public:
    CameraFollower(GameObject& associated);

    void Start() override;
    void Update(float dt) override;
    void Render() override;

    ComponentType GetType() const override;
    static const ComponentType Type = ComponentType::CameraFollower;
};
