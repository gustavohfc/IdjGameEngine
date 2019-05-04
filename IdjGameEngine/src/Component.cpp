#include "pch.h"
#include "Component.h"


Component::Component(GameObject& associated):
    associated(associated) {}


Component::~Component() {}

void Component::NotifyCollision(GameObject& other) {}
