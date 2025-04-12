#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <map>
#include <string>
#include <memory>

class AudioManager
{
private:
	std::map<int, Mix_Chunk*> m_soundEffects;
	Mix_Music* m_music;
	bool m_initialized;
	int m_soundVolume;
	int m_musicVolume;
public:
	AudioManager();
	~AudioManager();

	/*
	* Khởi tạo hệ thống âm thanh
	* @param freq Tần số âm thanh
	* @param chunkSize Kích thước buffer
	* @return true nếu khởi tạo thành công
	*/
	bool init(int freq = 44100, int chunkSize = 2048);

	/*
	* Phát 1 hiệu ứng âm thanh
	* @param id ID của âm thanh
	* @param loops Số lần lặp lại
	* @param channel Kênh phát
	* @return ID của channel đang phát âm thanh
	*/
	int playSound(const int id, int loops = 0, int channel = -1);

	/*
	* Phát nhạc nền
	* @param loops Số lần lặp lại
	* @return true nếu phát thành công
	*/
	bool playMusic(int loops = -1);

	void clean();
};