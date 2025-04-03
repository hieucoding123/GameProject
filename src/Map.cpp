#include <fstream>
#include "Map.h"
#include "GameObjects/Tile.h"
#include "Const.h"

Map::Map()
{

}

Map::~Map()
{

}

void Map::LoadMap(const char* path)
{
	std::fstream myFile;
	myFile.open(path);

	int ID;

	for (int y = 0; y < FILE_ROW; y++)
	{
		for (int x = 0; x < FILE_COL; x++)
		{
			myFile >> ID;

			int tileX = (ID % COL) * BLOCK_W;
			int tileY = (ID / ROW) * BLOCK_H;
			tiles.push_back(std::make_unique<Tile>(tileX, tileY, x * BLOCK_W, y * BLOCK_H));

			myFile.ignore();
		}
	}
	myFile.close();
}

void Map::update()
{
	for (auto& t : tiles)
	{
		t->update();
	}
}

void Map::draw()
{
	for (auto& t : tiles)
	{
		t->draw();
	}
}

void Map::clean()
{
	tiles.clear();
}