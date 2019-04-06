#include "pch.h"
#include "Face.h"
#include "Sound.h"


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


void Face::Update(float dt) {}

void Face::Render() {}


bool Face::Is(const std::string& type) {
    return type == "Face";
}
