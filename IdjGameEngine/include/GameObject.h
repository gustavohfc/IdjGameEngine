#pragma once
#include "Rect.h"
#include "Component.h"

class Component;
class Sound;
class Minion;
class Sprite;
class Collider;

class GameObject {
public:
    Rect box;
    double angleDeg;

    GameObject();
    ~GameObject();

    void Start();
    void Update(float dt);
    void Render();
    bool IsDead() const;
    void RequestDelete();
    void AddComponent(const std::shared_ptr<Component>& cpt);
    void RemoveComponent(const std::shared_ptr<Component>& cpt);
    Vec2 GetPosition() const;
    void NotifyCollision(GameObject& other);

    std::shared_ptr<Component> GetComponent(const std::string& type) const;
    std::shared_ptr<Sound> GetSound() const;
    std::shared_ptr<Minion> GetMinion() const;
    std::shared_ptr<Sprite> GetSprite() const;
    std::shared_ptr<Collider> GetCollider() const;

private:
    std::vector<std::shared_ptr<Component>> components;
    bool isDead = false;
    bool started = false;
};
