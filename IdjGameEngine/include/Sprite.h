#pragma once
#include "Component.h"

class Sprite : public Component {
public:
    Sprite(GameObject& associated);
    Sprite(const std::string& file);
    Sprite(GameObject& associated, const std::string& file);
    ~Sprite();

    void Open(const std::string& file);
    void SetClip(int x, int y, int w, int h);
    int GetWidth() const;
    int GetHeight() const;
    bool IsOpen() const;
    void Render(int x, int y, int w, int h);

    void Render() override;
    void Update(float dt) override;
    bool Is(const std::string& type) override;

private:
    SDL_Texture* texture = nullptr;
    int width;
    int height;
    SDL_Rect clipRect;
};
