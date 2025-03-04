#include <fstream>
#include "Map.h"
#include "TextureManager.h"
#include "Const.h"

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
			Game::addTile(tileX, tileY, x * BLOCK_H, y * BLOCK_W);

			myFile.ignore();
		}
	}
	myFile.close();
}