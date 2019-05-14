#pragma once
#include "Component.h"
#include "Rect.h"

class Collider : public Component {
public:
    Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});

    Rect box;
  
    void Start() override;
    void Update(float dt) override;
    void Render() override;

    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);

    ComponentType GetType() const override;
    static const ComponentType Type = ComponentType::Collider;

private:
    Vec2 scale;
    Vec2 offset;
};
