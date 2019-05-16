#pragma once

class GameObject;

enum class ComponentType {
	Alien,
	Bullet,
	CameraFollower,
	Collider,
	Minion,
	PenguinBody,
	PenguinCannon,
	Sound,
	Sprite,
	TileMap
};

class Component {
public:
	Component(GameObject& associated);
	virtual ~Component();

	virtual void Start() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual void NotifyCollision(GameObject& other);

	virtual ComponentType GetType() const = 0;

protected:
	GameObject& associated;
};
