#include <fstream>
#include "Map.h"
#include "TextureManager.h"
#include "Const.h"

Map::Map()
{

}

Map::~Map()
{

}

// tải và vẽ map

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
			PlaySection::tiles.push_back(std::move(std::make_unique<Tile>(tileX, tileY, x * BLOCK_W, y * BLOCK_H)));

			myFile.ignore();
		}
	}
	myFile.close();
}