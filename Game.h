#pragma once

#include <iostream>
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
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};