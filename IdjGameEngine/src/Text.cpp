#include "pch.h"
#include "Text.h"
#include "Game.h"
#include "Camera.h"
#include "Resources.h"
#include "Constants.h"


Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color):
	Component(associated),
	font(nullptr),
	texture(nullptr),
	text(text),
	style(style),
	fontFile(fontFile),
	fontSize(fontSize),
	color(color) {

	RemakeTexture();
}


Text::~Text() {
	// TODO: destroy texture?
}


void Text::Start() {}

void Text::Update(float dt) {}


void Text::Render() {
	if (texture == nullptr) {
		return;
	}

	auto renderer = Game::GetInstance().GetRenderer();

	SDL_Rect clipRect = {
		0,
		0,
		int(associated.box.w),
		int(associated.box.h)
	};

	SDL_Rect dstRect = {
		int(associated.box.x - Camera::pos.x),
		int(associated.box.y - Camera::pos.y),
		int(associated.box.w),
		int(associated.box.h)
	};

	SDL_RenderCopyEx(renderer, texture.get(), &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}


void Text::SetText(std::string text) {
	this->text = text;
	RemakeTexture();
}


void Text::SetColor(SDL_Color color) {
	this->color = color;
	RemakeTexture();
}


void Text::SetStyle(TextStyle style) {
	this->style = style;
	RemakeTexture();
}


void Text::SetFontFile(std::string fontFile) {
	this->fontFile = fontFile;
	RemakeTexture();
}


void Text::SetFontSize(int fontSize) {
	this->fontSize = fontSize;
	RemakeTexture();
}


void Text::RemakeTexture() {
	font = Resources::GetFont(fontFile, fontSize);

	SDL_Surface* surface;

	switch (style) {
		case SOLID:
			surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
			break;

		case SHADED:
			surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, Constants::Color::BLACK);
			break;

		case BLENDED:
			surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
			break;

		default:
			throw std::logic_error("Style not implemented");
	}

	if (surface == nullptr) {
		throw std::runtime_error("TTF_RenderText fail!");
	}

	associated.box.w = float(surface->w);
	associated.box.h = float(surface->h);

	auto textureTemp = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
	if (textureTemp == nullptr) {
		throw std::runtime_error("SDL_CreateTextureFromSurface() fail!");
	}

	texture = std::shared_ptr<SDL_Texture>(textureTemp, [](SDL_Texture* p) { SDL_DestroyTexture(p); });

	SDL_FreeSurface(surface);
}
