#pragma once

class Resources {
public:
	static std::shared_ptr<SDL_Texture> GetImage(const std::string& file);
	static std::shared_ptr<Mix_Music> GetMusic(const std::string& file);
	static std::shared_ptr<Mix_Chunk> GetSound(const std::string& file);
	static void ClearImages();
	static void ClearMusics();
	static void ClearSounds();

private:
	static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
	static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
	static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
};
