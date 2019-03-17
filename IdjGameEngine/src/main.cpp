#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
	SDL_Window* window = SDL_CreateWindow("Meu Jogo daora", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 600, 0);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	SDL_Texture* texture = IMG_LoadTexture(renderer, "resources/img/ocean.jpg");
	int textureWidth, textureHeight;
	SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);

	SDL_Rect sourceRect = { 0, 0, textureWidth, textureHeight };
	SDL_Rect onScreenRect = { 0, 0, 1024, 600 };
	SDL_RenderCopyEx(renderer, texture, &sourceRect, &onScreenRect, 0, nullptr, SDL_FLIP_NONE);

	TTF_Init();
	int fontsize = 12;
	SDL_Color color = { 0, 0, 0, 0 };
	int fontTextureWidth, fontTextureHeight;
	TTF_Font* font = TTF_OpenFont("resources/font/Call me maybe.ttf", fontsize);
	SDL_Surface* surf = TTF_RenderText_Blended(font, "SDL INSTALADA!", color);
	SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_QueryTexture(fontTexture, nullptr, nullptr, &fontTextureWidth, &fontTextureHeight);
	SDL_Rect fontSourceRect = { 0, 0, fontTextureWidth, fontTextureHeight };
	SDL_Rect fontOnScreenRect = { 512 - fontTextureWidth / 2,
								300 - fontTextureHeight / 2,
							  fontTextureWidth, fontTextureHeight };

	SDL_RenderCopyEx(renderer, fontTexture, &fontSourceRect, &fontOnScreenRect, 0, nullptr, SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
	Mix_Music* music = Mix_LoadMUS("resources/audio/stageState.ogg");
	Mix_PlayMusic(music, 1);

	while (true) {
		if (SDL_QuitRequested()) {
			break;
		}
	}

	Mix_FreeMusic(music);
	Mix_CloseAudio();
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}