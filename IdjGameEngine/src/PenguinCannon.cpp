#include "pch.h"
#include "PenguinCannon.h"
#include "Sprite.h"
#include "Util.h"
#include "InputManager.h"
#include "Game.h"
#include "Bullet.h"
#include "Collider.h"


PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody):
    Component(associated),
    pbody(penguinBody),
    angle(0) {

    associated.AddComponent(std::make_shared<Sprite>(associated, "assets/img/cubngun.png"));
    associated.AddComponent(std::make_shared<Collider>(associated));
}


void PenguinCannon::Start() {}


void PenguinCannon::Update(float dt) {
    auto pbody = this->pbody.lock();
    if (!pbody) {
        associated.RequestDelete();
        return;
    }

    auto& inputManager = InputManager::GetInstance();

    angle = Vec2::GetVectorBetweenTwoPoints(associated.box.GetCenter(), inputManager.GetMouseMapPos()).Angle();

    associated.box.SetCenter(pbody->box.GetCenter());
    associated.angleDeg = Util::RadToDeg(angle);

    if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        Shoot();
    }
}


void PenguinCannon::Render() {}


bool PenguinCannon::Is(const std::string& type) {
    return type == "PenguinCannon";
}


void PenguinCannon::Shoot() {
    auto state = Game::GetInstance().GetState();

    auto cannonCenter = associated.box.GetCenter();
    auto cannonTip = cannonCenter + Vec2(54, 0).GetRotated(-angle);

    auto bulletGO = std::make_shared<GameObject>();
    bulletGO->AddComponent(std::make_shared<Bullet>(*bulletGO, angle, 100, 10, 1000, "assets/img/minionbullet2.png", 3, 1));
    bulletGO->box.SetCenter(cannonTip.x, cannonTip.y);
    bulletGO->angleDeg = Util::RadToDeg(angle);
    state->AddObject(bulletGO);
}
