#include "pch.h"
#include "Face.h"
#include "Sound.h"
#include "InputManager.h"


Face::Face(GameObject& associated):
    Component(associated),
    hitpoints(30) {}


void Face::Damage(int damage) {
    hitpoints -= damage;

    if (hitpoints < 0) {
        associated.RequestDelete();

        auto sound = associated.GetSound();
        if (sound != nullptr) {
            sound->Play();
        }
    }
}


void Face::Update(float dt) {
    auto& inputManager = InputManager::GetInstance();

    if (inputManager.MousePress(LEFT_MOUSE_BUTTON) && associated.box.Contains(inputManager.GetMouseMapPos())) {

        Damage(std::rand() % 10 + 10);
    }
}


void Face::Render() {}


bool Face::Is(const std::string& type) {
    return type == "Face";
}
