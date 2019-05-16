#pragma once

class Music {
public:
	Music();
	Music(const std::string& file);

	void Play(int times = -1) const;
	void Stop(int msToStop = 1500);
	void Open(const std::string& file);
	bool IsOpen() const;

private:
	std::shared_ptr<Mix_Music> music = nullptr;
};
