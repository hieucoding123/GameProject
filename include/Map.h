#pragma once

#include "TextureManager.h"
#include "GameObjects/Tile.h"
#include <string>

class Map
{
public:
	Map();
	~Map();

	void LoadMap(const char* path);
};