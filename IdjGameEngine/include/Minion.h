#pragma once
#include "Component.h"


class Minion : public Component {
public:
    Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffset = 0);

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(const std::string& type) override;

private:
    std::weak_ptr<GameObject> alienCenter;
    float arc;
};
