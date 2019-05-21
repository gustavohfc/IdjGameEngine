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
	void RemoveComponent(const Component* cpt);
	Vec2 GetPosition() const;
	void NotifyCollision(GameObject& other);

	template <class T, class ... TArgs>
	T* AddComponent(TArgs&& ... args);

	template <class T>
	T* GetComponent() const;


private:
	std::vector<std::unique_ptr<Component>> components;
	std::array<Component*, Constants::NUMBER_OF_COMPONENTS_TYPES> componentsArray{};

	bool isDead = false;
	bool started = false;
};


template <class T, class... TArgs>
T* GameObject::AddComponent(TArgs&&... args) {

	auto cpt = new T(*this, std::forward<TArgs>(args)...);

	components.emplace_back(cpt);
	componentsArray[GetComponentTypeId<T>()] = cpt;

	if (started) {
		cpt->Start();
	}

	return cpt;
}


template <class T>
T* GameObject::GetComponent() const {
	static_assert(std::is_base_of<Component, T>::value, "Invalid type");
	return static_cast<T*>(componentsArray[GetComponentTypeId<T>()]);
}
