#pragma once
#include "Rect.h"
#include "Component.h"

class Component;
class Sound;
class Face;

class GameObject {
public:
    Rect box;

    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();
    bool IsDead() const;
    bool ReadyToBeDeleted() const;
    void RequestDelete();
    void AddComponent(const std::shared_ptr<Component>& cpt);
    void RemoveComponent(const std::shared_ptr<Component>& cpt);
    std::shared_ptr<Component> GetComponent(const std::string& type) const;
    std::shared_ptr<Sound> GetSound() const;
    std::shared_ptr<Face> GetFace() const;

private:
    std::vector<std::shared_ptr<Component>> components;
    bool isDead;
};
