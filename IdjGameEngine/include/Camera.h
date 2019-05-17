#pragma once
#include "GameObject.h"

class Camera {
public:
	static void Follow(GameObject* newFocus);
	static void Unfollow();
	static void Update(float dt);
	static void Reset();

	static Vec2 pos, speed;

private:
	static GameObject* focus;
};
