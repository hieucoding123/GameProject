#pragma once

#include <vector>

const int WIDTH = 800;
const int HIGH = 640;

const int FPS = 60;
const int frameDelay = 1000 / FPS;

const int BLOCK_W = 32;
const int BLOCK_H = 32;
const int MAP_SCALE = 1;

const int FILE_COL = 25;		// HIGH / BLOCK_H
const int FILE_ROW = 20;		// WIDTH / BLOCK_W

const int ROW = 15;
const int COL = 15;

const int DEFAULT_X1 = 64;
const int DEFAULT_X2 = 736;
const int DEFAULT_Y = 568;

constexpr const char* imageTilePath = "assets/imageTileMap.png";
constexpr const char* tileMapPath = "assets/TileMap.txt";

const std::vector<std::vector<int>> SASUKE = {
	// frames - speed - srcX - srcY - W - H
	{4, 150, 0,  0, 48, 75},		// idle
	{6, 110, 0, 75, 67, 75},			// walk
	{3, 200, 0, 150, 56, 75},		// jump
	{1, 1, 0, 150, 56, 75}
};