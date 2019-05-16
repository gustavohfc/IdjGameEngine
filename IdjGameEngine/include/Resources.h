#pragma once

class Resources {
public:
	static SDL_Texture* GetImage(const std::string& file);
	static Mix_Music* GetMusic(const std::string& file);
	static Mix_Chunk* GetSound(const std::string& file);
	static void ClearImages();
	static void ClearMusics();
	static void ClearSounds();

private:
	static std::unordered_map<std::string, SDL_Texture*> imageTable;
	static std::unordered_map<std::string, Mix_Music*> musicTable;
	static std::unordered_map<std::string, Mix_Chunk*> soundTable;
};
