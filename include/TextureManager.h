#pragma once

#include "Game.h"

// quản lý và cài texture
class TextureManager
{
public:

	static SDL_Texture* LoadTexture(const char* path);
};