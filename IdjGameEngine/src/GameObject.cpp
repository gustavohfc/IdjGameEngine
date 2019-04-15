#include "pch.h"
#include "GameObject.h"
#include "Sound.h"
#include "Face.h"


GameObject::GameObject() {}


GameObject::~GameObject() {
    components.clear();
}


void GameObject::Start() {
    for (auto& component : components) {
        component->Start();
    }

    started = true;

    // TODO: Start new components from AddComponent??
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
}


void GameObject::RemoveComponent(const std::shared_ptr<Component>& cpt) {
    auto it = std::find_if(components.begin(), components.end(),
                           [&cpt](const std::shared_ptr<Component>& c) { return c == cpt; });

    if (it != components.end()) {
        components.erase(it);
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


std::shared_ptr<Face> GameObject::GetFace() const {
    return std::static_pointer_cast<Face>(GetComponent("Face"));
}
