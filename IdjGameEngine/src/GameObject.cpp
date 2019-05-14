#include "pch.h"
#include "GameObject.h"
#include "Sound.h"
#include "Minion.h"
#include "Sprite.h"
#include "Collider.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Bullet.h"


GameObject::GameObject():
    angleDeg(0) {}


GameObject::~GameObject() {
    components.clear();
}


void GameObject::Start() {
    for (auto& component : components) {
        component->Start();
    }

    started = true;
}


void GameObject::Update(float dt) {
    for (auto& component : components) {
        component->Update(dt);
    }
}


void GameObject::Render() {
    for (auto& component : components) {
        component->Render();
    }
}


bool GameObject::IsDead() const {
    return isDead;
}


void GameObject::RequestDelete() {
    isDead = true;
}


void GameObject::AddComponent(const std::shared_ptr<Component>& cpt) {
    components.push_back(cpt);

    if (started) {
        cpt->Start();
    }
}


void GameObject::RemoveComponent(const std::shared_ptr<Component>& cpt) {
    auto it = std::find_if(components.begin(), components.end(),
                           [&cpt](const std::shared_ptr<Component>& c) { return c == cpt; });

    if (it != components.end()) {
        components.erase(it);
    }
}


Vec2 GameObject::GetPosition() const {
    return box.GetCenter();
}


void GameObject::NotifyCollision(GameObject& other) {
    for (int i = 0; i < components.size(); i++) {
        components[i]->NotifyCollision(other);
    }
}
