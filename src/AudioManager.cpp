﻿#include "AudioManager.h"
#include "Const.h"
#include <iostream>

AudioManager::AudioManager() 
	:m_music(nullptr), m_initialized(false),
	m_soundVolume(MIX_MAX_VOLUME), m_musicVolume(MIX_MAX_VOLUME / 2)
{

}

AudioManager::~AudioManager()
{
	clean();
}

bool AudioManager::init(int freq, int chunkSize)
{
	if (Mix_OpenAudio(freq, MIX_DEFAULT_FORMAT, 2, chunkSize) < 0)
	{
		std::cerr << "SDL_mixer không thể khởi tạo! SDL_mixer Error: "
			<< Mix_GetError() << std::endl;
		return false;
	}

	// Thiết lập số lượng kênh âm thanh (16 kênh mặc định)
	Mix_AllocateChannels(16);

	m_initialized = true;

	// giải phóng nhạc nền hiện tại nếu có
	if (m_music)
	{
		Mix_FreeMusic(m_music);
		m_music = nullptr;
	}

	m_music = Mix_LoadMUS(MUSIC_PATH);

	if (!m_music) {
		std::cerr << "Không thể tải nhạc nền! SDL_mixer Error: "
			<< Mix_GetError() << std::endl;
		return false;
	}
	Mix_VolumeMusic(m_musicVolume);
	Mix_PlayMusic(m_music, -1);

	// khởi tạo tất cả âm thanh
	for (int i = 0; i < SOUND_PAHTS.size(); i++)
	{
		m_soundEffects[i] = Mix_LoadWAV(SOUND_PAHTS[i]);
	}

	return true;
}

int AudioManager::playSound(const int id, int loops, int channel)
{
	if (!m_initialized)
		return false;

	auto it = m_soundEffects.find(id);
	if (it == m_soundEffects.end())
	{
		std::cerr << "Sound effect ID '" << id << "' không tồn tại!" << std::endl;
		return -1;
	}

	channel = Mix_PlayChannel(channel, it->second, loops);
	if (channel == -1)
	{
		std::cerr << "Không thể phát sound effect! SDL_mixer Error: "
			<< Mix_GetError() << std::endl;
	}

	return channel;
}

bool AudioManager::playMusic(int loops)
{
	if (!m_initialized || !m_music)
		return false;

	if (Mix_PlayMusic(m_music, loops) == -1)
	{
		std::cerr << "Không thể phát nhạc nền! SDL_mixer Error: "
			<< Mix_GetError() << std::endl;
		return false;
	}

	return true;
}

void AudioManager::stopMusic()
{
	if (m_initialized)
	{
		Mix_HaltMusic();
	}
}

void AudioManager::stopSound(int channel)
{
	if (m_initialized)
	{
		Mix_HaltChannel(channel);
	}
}

void AudioManager::pauseMusic()
{
	if (m_initialized)
		Mix_PausedMusic();
}

void AudioManager::resumeMusic()
{
	if (m_initialized)
		Mix_ResumeMusic();
}

void AudioManager::setSoundVolume(int volume)
{
	m_soundVolume = (volume < 0) ? 0 : ((volume > MIX_MAX_VOLUME) ? MIX_MAX_VOLUME : volume);

	// thiết lập volume cho tất các các kênh
	Mix_Volume(-1, m_soundVolume);
}

void AudioManager::setMusicVolume(int volume)
{
	m_musicVolume = (volume < 0) ? 0 : ((volume > MIX_MAX_VOLUME) ? MIX_MAX_VOLUME : volume);

	// Thiết lập volume cho nhạc nền
	Mix_VolumeMusic(m_musicVolume);
}

void AudioManager::clean()
{
	if (m_initialized)
	{
		for (auto& pair : m_soundEffects)
		{
			Mix_FreeChunk(pair.second);
		}
		m_soundEffects.clear();

		// giải phóng nhạc nền
		if (m_music)
		{
			Mix_FreeMusic(m_music);
		}

		// đóng audio
		Mix_CloseAudio();
		m_initialized = false;
	}
}