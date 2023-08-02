#include "Audio.h"
#include "../core/Application.h"

Audio::Audio(Mix_Chunk* audio)
{
	m_audio = audio;
}

Audio::~Audio()
{
	Mix_FreeChunk(m_audio);
}

void Audio::SetAudio(Mix_Chunk* audio)
{
	if (m_audio != nullptr) Mix_FreeChunk(m_audio);

	m_audio = audio;
}

void Audio::SetVolume(int volume)
{
	Mix_VolumeChunk(m_audio, volume);
}

void Audio::SetChannel(int _channel)
{
	channel = _channel;
}

void Audio::Play(int loop) {
	Mix_PlayChannel(channel, m_audio, loop);
}

void Audio::Pause() {
	Mix_Pause(channel);
}

void Audio::Resume() {
	Mix_Resume(channel);
}

Mix_Chunk* AudioLoader::LoadAudio(const std::string& filename)
{
	std::string path = Application::Get().GetAssetsPath() + "\\audio\\" + filename;

	return Mix_LoadWAV(path.c_str());
}
