#pragma once

#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include <vector>
#include "Effect.h"

class Effect;

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
	static SDL_Event event;
	static SDL_Rect camera;
	static std::vector<Effect*> effects;

	static int MAP_SCALE;
	static void addTile(int tileX, int tileY, int xpos, int ypos);
	static bool AABB(const SDL_Rect& rect1, const SDL_Rect& rect2);
private:
	bool isRunning;
	SDL_Window* window;
};