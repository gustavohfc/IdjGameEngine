#pragma once
#include "Component.h"
#include "Timer.h"
#include "Rect.h"

class Sprite : public Component {
public:
	Sprite(GameObject& associated, const std::string& file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);

	void Open(const std::string& file);
	void SetClip(int x, int y, int w, int h);
	int GetWidth() const;
	int GetHeight() const;
	bool IsOpen() const;
	void Render(int x, int y, int w, int h);
	void SetScale(float scaleX, float scaleY);
	Vec2 GetScale() const;

	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);

	void Start() override;
	void Render() override;
	void Update(float dt) override;

	ComponentType GetType() const override;
	static const ComponentType Type = ComponentType::Sprite;

private:

	void UpdateFrameClipRect();

	SDL_Texture* texture = nullptr;
	int width;
	int height;
	SDL_Rect clipRect;

	int frameCount;
	int currentFrame;
	float timeElapsed;
	float frameTime;

	Vec2 scale;

	Timer selfDestructCount;
	float secondsToSelfDestruct;
};
