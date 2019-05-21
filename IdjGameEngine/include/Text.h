#pragma once
#include "Component.h"

class Text : public Component {
public:
	enum TextStyle { SOLID, SHADED, BLENDED };

	Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);
	~Text();

	void Start() override;
	void Update(float dt) override;
	void Render() override;

	void SetText(std::string text);
	void SetColor(SDL_Color color);
	void SetStyle(TextStyle style);
	void SetFontFile(std::string fontFile);
	void SetFontSize(int fontSize);

private:
	void RemakeTexture();

	std::shared_ptr<TTF_Font> font;
	std::shared_ptr<SDL_Texture> texture;

	std::string text;
	TextStyle style;
	std::string fontFile;
	int fontSize;
	SDL_Color color;
};
