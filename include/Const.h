#pragma once

#include "SDL.h"
#include <unordered_map>
#include <map>
#include <vector>

const int WIDTH = 800;
const int HIGH = 640;

const int FPS = 60;
const int frameDelay = 1000 / FPS;

const int BLOCK_W = 32;			// kích cỡ tile trong ảnh gốc
const int BLOCK_H = 32;
//const int MAP_SCALE = 2;		// tỉ lệ phóng to map

const int FILE_COL = 25;		// HIGH / BLOCK_H
const int FILE_ROW = 20;		// WIDTH / BLOCK_W

const int ROW = 15;
const int COL = 15;

const int DEFAULT_X1 = 64;
const int DEFAULT_X2 = 736;
const int DEFAULT_Y = 568;

const int GROUND = 568;
const int GRAVITY = 7;

const int PLAYER1ID = 1;
const int PLAYER2ID = 2;

const double HP = 500;
const double ENERGY = 2000;
const int DEFENSE = 10;

// chiều dài và rộng thanh máu
const int HP_W = 200;
const int HP_H = 20;

// màu nền và màu thanh máu và thanh năng lượng
const SDL_Color HPBG_COLOR = { 255, 0, 0, 255 };
const SDL_Color HP_COLOR = { 234, 164, 31, 255 };

const SDL_Color ENGBG_COLOR = { 155, 159, 191, 255 };
const SDL_Color ENG_COLOR = { 73, 222, 255, 255 };

constexpr const char* imageTilePath = "assets/imageTileMap.png";
constexpr const char* tileMapPath = "assets/TileMap.txt";

const std::unordered_map<int, const std::map<const char*, std::vector<int>>> GAMECHARACTERS = {
		// frames - speed - srcX - srcY - W - H - isHitting - damage
	{ 1, {{ "idle", {4, 150, 0,  0, 48, 75, 0, 0} },		// idle
		{ "run", {6, 110, 0, 75, 67, 75, 0, 0}},			// walk
		{ "jump", {3, 200, 0, 150, 56, 75, 0, 0}},		// jump
		{ "fall", {1, 1, 0, 150, 56, 74, 0, 0}},
		{ "guard", {1, 1, 0, 224, 58, 71, 0, 0}},
		{"airguard", {1, 1, 0, 296, 58, 74, 0, 0}},
		{"attackcb", {7, 180, 0, 371, 91, 75, 1, 20}},
		{"skill1", {8, 140, 0, 446, 60, 77, 1, 35}},
		{"fire", {6, 110, 0, 523, 86, 57, 1, 35}}}},
	{ 2, {{"idle", {6, 150, 0, 0, 46, 80, 0, 0}},
		{"attackcb", {9, 110, 0, 80, 88, 86, 1, 30}},
		{"run", {8, 150, 0, 166, 58, 77, 0, 0}},
		{"jump", {3, 200, 0, 243, 68, 84, 0, 0}}}}
};

const std::vector<const char*> MASKS = {
	"assets/fight/p1.png",
	"assets/fight/p2.png"
};

const int MASK_W = 39;
const int MASK_H = 55;