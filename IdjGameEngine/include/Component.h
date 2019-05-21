#pragma once
#include "Constants.h"

class GameObject;

class Component {
public:
	Component(GameObject& associated);
	virtual ~Component();

	virtual void Start() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual void NotifyCollision(GameObject& other);

protected:
	GameObject& associated;
};


inline unsigned GetNextComponentId() {
	static auto lastId = 0u;
	return lastId++;
}


template <typename T>
unsigned GetComponentTypeId() {
	static_assert(std::is_base_of<Component, T>::value, "");
	static auto typeId = GetNextComponentId();
	return typeId;
}
