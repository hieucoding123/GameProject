#pragma once

#include <iostream>
#include <SDL_image.h>
#include <SDL.h>

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

	static SDL_Renderer* renderer;
private:
	bool isRunning;
	SDL_Window* window;
};