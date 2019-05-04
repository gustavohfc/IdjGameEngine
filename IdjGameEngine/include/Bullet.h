#pragma once
#include "Component.h"

class Bullet : public Component {
public:
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, const std::string& sprite, int frameCount,
           float frameTime, bool targetsPlayer);

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(const std::string& type) override;
    void NotifyCollision(GameObject& other) override;

    int GetDamage() const;

    bool targetsPlayer;

private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};
