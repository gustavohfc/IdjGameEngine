#pragma once
#include "Component.h"

class Sound : public Component {
public:
    Sound(GameObject& associated);
    Sound(GameObject& associated, const std::string& file);
    ~Sound();

    void Play(int times = 1);
    void Stop();
    void Open(const std::string& file);
    bool IsOpen();
    bool IsPlaying() const;

    void Update(float dt) override;
    void Render() override;
    bool Is(const std::string& type) override;

private:
    Mix_Chunk* chunk = nullptr;
    int channel = -1;
};
