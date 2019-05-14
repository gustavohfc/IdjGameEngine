#include "pch.h"
#include "CameraFollower.h"
#include "Camera.h"


CameraFollower::CameraFollower(GameObject& associated) :
    Component(associated) {}


void CameraFollower::Start() {}


void CameraFollower::Update(float dt) {
    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;
}


void CameraFollower::Render() {}


ComponentType CameraFollower::GetType() const {
    return Type;
}
