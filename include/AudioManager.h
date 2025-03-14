#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <map>
#include <string>
#include <memory>

class AudioManager
{
private:
	std::map<std::string, Mix_Chunk*> m_soundEffects;
	Mix_Music* m_music;
	bool m_initialized;
	int m_soundVolume;
	int m_musicVolume;
public:
	AudioManager();
	~AudioManager();

	/*
	* Khởi tạo hệ thống âm thanh
	* @param freq Tần số âm thanh (Hz), mặc định 44100
	* @param chunkSize Kích thước buffer (bytes)
	* @return true nếu khởi tạo thành công
	*/
	bool init(int freq = 44100, int chunkSize = 2048);

	/*
	* Tải file âm thanh hiệu ứng
	* @param id ID để tham chiếu đến sound
	* @param filePath Đường đẫn đến file âm thang
	* @return true nếu tải thành công
	*/
	bool loadSound(const std::string& id, const char* filePath);

	/*
	* Tải file nhạc nền
	* @param filePath Đường dẫn đến file nhạc
	* @return true nếu tải thành công
	*/
	bool loadMusic(const char* filePath);

	/*
	* Phát 1 hiệu ứng âm thanh
	* @param id ID của âm thanh
	* @param loops Số lần lặp lại (-1 ~ lặp vô hạn)
	* @param channel Kênh phát (-1 ~ kênh trống đầu tiên)
	* @return ID của channel đang phát âm thanh
	*/
	int playSound(const std::string& id, int loops = -1, int channel = -1);

	/*
	* Phát nhạc nền
	* @param loops Số lần lặp lại (-1 ~ lặp vô hạn)
	* @return true nếu phát thành công
	*/
	bool playMusic(int loops = -1);

	/*
	* Dừng phát nhạc nền
	*/
	void stopMusic();

	/*
	* Dừng phát hiệu ứng âm thanh cụ thể
	* @param channel Kênh cần dừng (-1 = tất cả các kênh)
	*/
	void stopSound(int channel = -1);

	/*
	* Tạm dừng/tiếp tục phát nhạc nền
	*/
	void pauseMusic();
	void resumeMusic();

	/*
	 * Thiết lập âm lượng hiệu ứng âm thanh
	 * @param volume Âm lượng (0-128)
	 */
	void setSoundVolume(int volume);

	/*
	 * Thiết lập âm lượng nhạc nền
	 * @param volume Âm lượng (0-128)
	 */
	void setMusicVolume(int volume);

	/*
	 * Giải phóng tài nguyên âm thanh
	 */
	void clean();
};