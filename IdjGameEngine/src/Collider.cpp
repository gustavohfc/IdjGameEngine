#include "pch.h"
#include "Collider.h"
#include "Util.h"
#include "Game.h"
#include "Camera.h"


Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset):
	Component(associated),
	scale(scale),
	offset(offset) {}


void Collider::Start() {}


void Collider::Update(float dt) {
	box = {
		associated.box.x,
		associated.box.y,
		associated.box.w * scale.x,
		associated.box.h * scale.y,
	};

	auto goCenter = associated.box.GetCenter();
	box.SetCenter(goCenter + offset.GetRotated(Util::DegToRad(associated.angleDeg)));
}


void Collider::Render() {
#ifdef _DEBUG
	Vec2 center(box.GetCenter());
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).GetRotated(float(associated.angleDeg / (180 / M_PI))) + center - Camera::pos;

	points[0] = {int(point.x), int(point.y)};
	points[4] = {int(point.x), int(point.y)};

	point = (Vec2(box.x + box.w, box.y) - center).GetRotated(float(associated.angleDeg / (180 / M_PI)))
		+ center - Camera::pos;

	points[1] = {int(point.x), int(point.y)};

	point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated(float(associated.angleDeg / (180 / M_PI)))
		+ center - Camera::pos;

	points[2] = {int(point.x), int(point.y)};

	point = (Vec2(box.x, box.y + box.h) - center).GetRotated(float(associated.angleDeg / (180 / M_PI)))
		+ center - Camera::pos;

	points[3] = {int(point.x), int(point.y)};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}


void Collider::SetScale(Vec2 scale) {
	this->scale = scale;
}


void Collider::SetOffset(Vec2 offset) {
	this->offset = offset;
}
