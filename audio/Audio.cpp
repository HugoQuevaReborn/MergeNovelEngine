#include "Audio.h"
#include "../core/Application.h"

Audio::Audio(Mix_Chunk* audio)
	: channel(0)
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

Mix_Chunk* AudioLoader::LoadAudio(const std::filesystem::path& filename)
{
	return Mix_LoadWAV((Application::Get().GetAssetsPath() / filename).string().c_str());
}