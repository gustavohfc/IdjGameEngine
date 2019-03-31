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
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(const std::string& type) const;
    Sound* GetSound() const;
    Face* GetFace() const;

private:
    std::vector<Component*> components;
    bool isDead;
};
