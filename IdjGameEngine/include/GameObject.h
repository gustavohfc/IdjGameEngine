#pragma once
#include "Rect.h"
#include "Component.h"

class Component;
class Sound;

class GameObject {
public:
    Rect box;

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

    std::shared_ptr<Component> GetComponent(const std::string& type) const;
    std::shared_ptr<Sound> GetSound() const;

private:
    std::vector<std::shared_ptr<Component>> components;
    bool isDead = false;
    bool started = false;
};
