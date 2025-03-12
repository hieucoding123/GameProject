﻿#pragma once

#include "SDL.h"
#include <unordered_map>
#include <map>
#include <vector>

const int WIDTH = 1920;
const int HIGH = 992;

const int FPS = 60;
const int frameDelay = 1000 / FPS;

const int BLOCK_W = 32;			// kích cỡ tile trong ảnh gốc
const int BLOCK_H = 32;
//const int MAP_SCALE = 2;		// tỉ lệ phóng to map

const int FILE_COL = 60;		// HIGH / BLOCK_H
const int FILE_ROW = 31;		// WIDTH / BLOCK_W

const int ROW = 15;
const int COL = 15;

const int DEFAULT_X1 = 64;
const int DEFAULT_X2 = 736;
const int DEFAULT_Y = 568;

const int GROUND = 960;
const int GRAVITY = 7;

const int PLAYER1ID = 1;
const int PLAYER2ID = 2;

const double HP = 500;
const double ENERGY = 2000;
const int DEFENSE = 10;

// chiều dài và rộng thanh máu
const int HP_W = 500;
const int HP_H = 30;

// màu nền và màu thanh máu và thanh năng lượng
const SDL_Color HPBG_COLOR = { 255, 0, 0, 255 };
const SDL_Color HP_COLOR = { 234, 164, 31, 255 };

const SDL_Color ENGBG_COLOR = { 155, 159, 191, 255 };
const SDL_Color ENG_COLOR = { 73, 222, 255, 255 };

constexpr const char* imageTilePath = "assets/imageTileMap.png";
constexpr const char* tileMapPath = "assets/TileMap.txt";

const std::map<int, std::vector<int>> SASUKE = {
	// state - f - s - x - y- w - h - hit - damage
	{ -1,				{4, 150, 0,  0, 48, 75, 0, 0} },		// idle
	{ (int)SDLK_d,		{6, 110, 0, 75, 67, 75, 0, 0}},			// walk
	{ (int)SDLK_w,		{3, 200, 0, 150, 56, 75, 0, 0}},		// jump
	{ -2,				{1, 1, 0, 150, 56, 74, 0, 0} },
	{ (int)SDLK_c,		{1, 1, 0, 224, 58, 71, 0, 0}},
	{ (int)SDLK_k,		{1, 1, 0, 296, 58, 74, 0, 0}},
	{ (int)SDLK_u,		{7, 180, 0, 371, 91, 75, 1, 20}},
	{ (int)SDLK_r,		{8, 100, 0, 446, 60, 77, 0, 0}},
	{ -3,				{7, 140, 242, 0, 86, 57, 1, 20} },
	{ -4,				{3, 250, 450, 77, 57, 73, 0, 0} }
};

const std::map<int, std::vector<int>> AKAINU = {
	// state - f - s - x - y- w - h - hit - damage
		{-1,			{6, 150, 0, 0, 46, 80, 0, 0}},
		{(int)SDLK_u,	{9, 110, 0, 80, 88, 86, 1, 20}},
		{(int)SDLK_d,	{8, 150, 0, 166, 58, 77, 0, 0}},
		{(int)SDLK_w,	{3, 200, 0, 243, 68, 84, 0, 0}},
		{(int)SDLK_r,	{8, 150, 0, 327, 84, 77, 0, 0}},
		{-3,			{12, 140, 303, 0, 68, 78, 1, 20}},
		{-4,			{1, 1000, 492, 169, 63, 74, 0, 0}}
};

const std::vector<const char*> MASKS = {
	"assets/fight/p1.png",
	"assets/fight/p2.png"
};

const int MASK_W = 39;
const int MASK_H = 55;