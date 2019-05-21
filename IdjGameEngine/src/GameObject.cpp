#include "pch.h"
#include "GameObject.h"
#include "Sound.h"
#include "Minion.h"
#include "PenguinBody.h"


GameObject::GameObject():
	angleDeg(0) {}


GameObject::~GameObject() {
}


void GameObject::Start() {
	for (auto& component : components) {
		component->Start();
	}

	started = true;
}


void GameObject::Update(float dt) {
	for (int i = components.size() - 1; i >= 0; i--) {
		components[i]->Update(dt);
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


void GameObject::RemoveComponent(const Component* cpt) {
	auto it = std::find_if(components.begin(), components.end(),
	                       [&cpt](const std::unique_ptr<Component>& c) { return c.get() == cpt; });

	if (it != components.end()) {
		components.erase(it);
	}

	for (auto& component : componentsArray) {
		if (component == cpt) {
			component = nullptr;
		}
	}
}


Vec2 GameObject::GetPosition() const {
	return box.GetCenter();
}


void GameObject::NotifyCollision(GameObject& other) {
	for (unsigned i = 0; i < components.size(); i++) {
		components[i]->NotifyCollision(other);
	}
}
