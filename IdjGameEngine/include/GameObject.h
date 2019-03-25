#pragma once
#include "Rect.h"
#include "Component.h"

class Component;

class GameObject {
public:
    Rect box;

    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(std::string type);

private:
    std::vector<Component*> components;
    bool isDead;
};
