#include "pch.h"
#include "GameObject.h"
#include "Sound.h"
#include "Minion.h"
#include "Sprite.h"
#include "Collider.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "PenguinCannon.h"


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


std::shared_ptr<Component> GameObject::GetComponent(const std::string& type) const {
    for (auto& component : components) {
        if (component->Is(type)) {
            return component;
        }
    }
    return nullptr;
}


std::shared_ptr<Sound> GameObject::GetSound() const {
    return std::static_pointer_cast<Sound>(GetComponent("Sound"));
}


std::shared_ptr<Minion> GameObject::GetMinion() const {
    return std::static_pointer_cast<Minion>(GetComponent("Minion"));
}


std::shared_ptr<Sprite> GameObject::GetSprite() const {
    return std::static_pointer_cast<Sprite>(GetComponent("Sprite"));
}

std::shared_ptr<Collider> GameObject::GetCollider() const {
    return std::static_pointer_cast<Collider>(GetComponent("Collider"));
}

std::shared_ptr<Alien> GameObject::GetAlien() const {
    return std::static_pointer_cast<Alien>(GetComponent("Alien"));
}

std::shared_ptr<PenguinBody> GameObject::GetPenguinBody() const {
    return std::static_pointer_cast<PenguinBody>(GetComponent("PenguinBody"));
}

std::shared_ptr<PenguinCannon> GameObject::GetPenguinCannon() const {
    return std::static_pointer_cast<PenguinCannon>(GetComponent("PenguinCannon"));
}