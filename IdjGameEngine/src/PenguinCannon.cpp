#include "pch.h"
#include "PenguinCannon.h"
#include "Sprite.h"
#include "Util.h"
#include "InputManager.h"


PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody):
    Component(associated),
    pbody(penguinBody),
    angle(0) {

    associated.AddComponent(std::make_shared<Sprite>(associated, "assets/img/cubngun.png"));
}


void PenguinCannon::Start() {}


void PenguinCannon::Update(float dt) {
    auto pbody = this->pbody.lock();
    if (!pbody) {
        associated.RequestDelete();
        return;
    }

    auto& inputManager = InputManager::GetInstance();

    associated.box.SetCenter(pbody->box.GetCenter());
    associated.angleDeg = Util::
        RadToDeg(Vec2::GetVectorBetweenTwoPoints(associated.box.GetCenter(), inputManager.GetMouseMapPos()).Angle());

    // TODO: Shoot
}


void PenguinCannon::Render() {}


bool PenguinCannon::Is(const std::string& type) {
    return type == "PenguinCannon";
}


void PenguinCannon::Shoot() {}
