#include "pch.h"
#include "Collider.h"
#include "Util.h"


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

void Collider::Render() {}

bool Collider::Is(const std::string& type) {
    return type == "Collider";
}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}
