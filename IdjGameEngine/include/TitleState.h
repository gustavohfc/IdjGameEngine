#pragma once
#include "State.h"
#include "Timer.h"

class TitleState : public State {
public:
	TitleState();
	~TitleState();

	void LoadAssets() override;
	void Update(float dt) override;
	void Render() override;

	void Start() override;
	void Pause() override;
	void Resume() override;

private:
	std::shared_ptr<GameObject> text;
	bool isTextTransparent = false;
	Timer textTimer;
};
