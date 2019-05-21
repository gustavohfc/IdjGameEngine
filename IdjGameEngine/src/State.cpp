#include "pch.h"
#include "State.h"
#include "Resources.h"


State::State():
	popRequested(false),
	quitRequested(false),
	started(false) {}


State::~State() {
	objectArray.clear();

	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();
	Resources::ClearFonts();
}


void State::AddObject(const std::shared_ptr<GameObject>& go) {
	objectArray.push_back(go);

	if (started) {
		go->Start();
	}
}


std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
	for (unsigned i = 0; i < objectArray.size(); i++) {
		if (go == objectArray[i].get()) {
			return objectArray[i];
		}
	}

	return std::weak_ptr<GameObject>();
}


bool State::PopRequested() const {
	return popRequested;
}


bool State::QuitRequested() const {
	return quitRequested;
}


void State::StartArray() {
	LoadAssets();

	for (unsigned i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}

	started = true;
}


void State::UpdateArray(float dt) {
	for (unsigned i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}
}


void State::RenderArray() {
	for (unsigned i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Render();
	}
}
