#pragma once
#include "Component.h"


class Minion : public Component {
public:
    Minion(GameObject& associated, const std::weak_ptr<GameObject>& alienCenter, double arcOffset = 0);

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(const std::string& type) override;

    void Shoot(Vec2 target) const;

private:
    std::weak_ptr<GameObject> alienCenter;
    float arc;
};