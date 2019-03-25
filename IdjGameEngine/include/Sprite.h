#pragma once

class Sprite {
public:
    Sprite();
    Sprite(std::string file);
    ~Sprite();

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    int GetWidth() const;
    int GetHeight() const;
    bool IsOpen() const;

private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
};
