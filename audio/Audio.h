#pragma once

#include <SDL2/SDL_mixer.h>
#include <filesystem>

class Audio
{
public:
	Audio(Mix_Chunk* audio);
	Audio() = default;
	~Audio();

	void SetAudio(Mix_Chunk* audio);
	void SetVolume(int volume);
	void SetChannel(int _channel);
	void Play(int loop = 0);
	void Pause();
	void Resume();

	int channel;
private:
	Mix_Chunk* m_audio;
};

class AudioLoader {
public:
	static Mix_Chunk* LoadAudio(const std::filesystem::path& filename);
};