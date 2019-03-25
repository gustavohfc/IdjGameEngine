#include "pch.h"
#include "GameObject.h"


GameObject::GameObject():
    isDead(false) {}


GameObject::~GameObject() {
    // TODO: Percorrer de tras para frente??
    for (auto component : components) {
        delete component;
    }

    components.clear();
}


void GameObject::Update(float dt) {
    for (auto component : components) {
        component->Update(dt);
    }
}


void GameObject::Render() {
    for (auto component : components) {
        component->Render();
    }
}


bool GameObject::IsDead() {
    return isDead;
}


void GameObject::RequestDelete() {
    isDead = true;
}


void GameObject::AddComponent(Component* cpt) {
    components.push_back(cpt);
}


void GameObject::RemoveComponent(Component* cpt) {
    auto it = std::find(components.begin(), components.end(), cpt);

    if (it != components.end()) {
        components.erase(it);
        // TODO: Delete?
    }
}


Component* GameObject::GetComponent(std::string type) {
    // TODO
    return nullptr;
}
