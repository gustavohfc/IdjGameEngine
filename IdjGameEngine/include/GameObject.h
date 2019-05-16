#pragma once
#include "Rect.h"
#include "Component.h"


class GameObject {
public:
	Rect box;
	float angleDeg;

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
	void NotifyCollision(GameObject& other);

	template <class T>
	std::shared_ptr<T> GetComponent() const;


private:
	std::vector<std::shared_ptr<Component>> components;
	bool isDead = false;
	bool started = false;
};


template <class T>
std::shared_ptr<T> GameObject::GetComponent() const {
	for (auto& component : components) {
		if (T::Type == component->GetType()) {
			return std::static_pointer_cast<T>(component);
		}
	}

	return nullptr;
}
