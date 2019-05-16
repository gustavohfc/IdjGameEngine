#pragma once
#include "Component.h"

class Sound : public Component {
public:
	Sound(GameObject& associated);
	Sound(GameObject& associated, const std::string& file);

	void Play(int times = 1);
	void Stop();
	void Open(const std::string& file);
	bool IsOpen();
	bool IsPlaying() const;

	void Start() override;
	void Update(float dt) override;
	void Render() override;

	ComponentType GetType() const override;
	static const ComponentType Type = ComponentType::Sound;

private:
	std::shared_ptr<Mix_Chunk> chunk = nullptr;
	int channel = -1;
};
