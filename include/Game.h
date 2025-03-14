#pragma once

#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include <vector>
#include <memory>
#include "AudioManager.h"

class Tile;
class EffectManager;

class Game
{
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int high, bool fullScreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; };

	static std::vector<std::unique_ptr<Tile>> tiles;
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static SDL_Rect camera;
	static EffectManager effectManager;

	static int MAP_SCALE;

	/*
	* Kiểm tra hai hình chữ nhật giao nhau
	* @param rect1 hình chữ nhật đầu tiên
	* @param rect2 hình chữ nhật thứ hai
	* @return true nếu hai hình giao nhau
	*/
	static bool AABB(const SDL_Rect& rec1, const SDL_Rect& rec2);

	/*
	* Phát một đoạn nhạc
	* @param int ID của đoạn nhạc
	*/
	static void playSound(int ID);
private:
	bool isRunning;
	SDL_Window* window;
	static std::unique_ptr<AudioManager> audioManager;
};