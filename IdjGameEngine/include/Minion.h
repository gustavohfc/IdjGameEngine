#pragma once
#include "Component.h"
#include "Rect.h"

class Minion : public Component {
public:
    Minion(GameObject& associated, const std::weak_ptr<GameObject>& alienCenter, double arcOffset = 0);

    void Start() override;
    void Update(float dt) override;
    void Render() override;

    void Shoot(Vec2 target) const;


    ComponentType GetType() const override;
    static const ComponentType Type = ComponentType::Minion;

private:
    std::weak_ptr<GameObject> alienCenter;
    float arc;
};
