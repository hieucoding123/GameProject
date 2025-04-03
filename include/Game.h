#pragma once

#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "AudioManager.h"


class Game
{
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int high, bool fullScreen);
	void play();
	void clean();
	bool running() { return isRunning; };

	static SDL_Renderer* renderer;
	static SDL_Event event;

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