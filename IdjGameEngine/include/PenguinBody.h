#pragma once
#include "Component.h"
#include "Vec2.h"

class PenguinBody : public Component {
public:
    PenguinBody(GameObject& associated);
    ~PenguinBody();

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    void NotifyCollision(GameObject& other) override;
    Vec2 GetCenter();

    ComponentType GetType() const override;
    static const ComponentType Type = ComponentType::PenguinBody;

    static PenguinBody* player;

private:
    void Die();

    std::weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;
};
