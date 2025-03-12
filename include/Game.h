#pragma once

#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include <vector>
#include <memory>

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

	static bool AABB(const SDL_Rect& rec1, const SDL_Rect& rec2);
private:
	bool isRunning;
	SDL_Window* window;
};