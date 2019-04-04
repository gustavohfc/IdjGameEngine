#include "pch.h"
#include "GameObject.h"
#include "Sound.h"
#include "Face.h"


GameObject::GameObject():
    isDead(false) {}


GameObject::~GameObject() {
    components.clear();
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


bool GameObject::ReadyToBeDeleted() const {
    return isDead && !GetSound()->IsPlaying();
}


void GameObject::RequestDelete() {
    isDead = true;
}


void GameObject::AddComponent(Component* cpt) {
    components.emplace_back(cpt);
}


void GameObject::RemoveComponent(Component* cpt) {
    auto it = std::find_if(components.begin(), components.end(),
                           [cpt](const std::unique_ptr<Component>& c) { return c.get() == cpt; });

    if (it != components.end()) {
        components.erase(it);
    }
}


Component* GameObject::GetComponent(const std::string& type) const {
    for (auto& component : components) {
        if (component->Is(type)) {
            return component.get();
        }
    }
    return nullptr;
}


Sound* GameObject::GetSound() const {
    return static_cast<Sound*>(GetComponent("Sound"));
}


Face* GameObject::GetFace() const {
    return static_cast<Face*>(GetComponent("Face"));
}
