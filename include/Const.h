﻿#pragma once

#include "SDL.h"
#include <unordered_map>
#include <map>
#include <vector>

constexpr const char* INTERFACE_PATH = "assets/interface.png";
constexpr const char* BUTTONS_PATH = "assets/buttons.png";

const int BUTTON_W = 100;
const int BUTTON_H = 34;

constexpr const char* SELECT_BG_IMG = "assets/selectBackground1.png";
constexpr const char* AVARTARS_IMG = "assets/avatars.png";
constexpr const char* SELECT_FRAME_IMG = "assets/selectFrame.png";
const int SELECT_X = 284;		// vị trí ban đầu của khung chọn
const int SELECT_Y = 387;		// vị trí ban đầu của khung chọn
const int SELECT_W = 70;		// chiều rộng khung chọn
const int SELECT_H = 94;		// chiều dài khung chọn
const int AVATAR_ROW = 1;		// số hàng xếp avatar
const int AVATAR_COL = 3;		// số cột xếp avatar

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

const int PLAYER1ID = 0;
const int PLAYER2ID = 1;
const int PLAYER3ID = 2;

const double HP = 500;
const double ENERGY = 300;
const int DEFENSE = 10;

// chiều dài và rộng thanh máu nhân vật
const int HP_W = 500;
const int HP_H = 30;

// máu bot
const double BOT_HP = 40;

// chiều dài và rộng thanh máu bot
const int BOT_HP_W = 100;
const int BOT_HP_H = 8;

const double BOSS_HP = 1000;
const int BOSS_HP_W = 300;
const int BOSS_HP_H = 20;

const int MAX_BOT = 3;

// màu nền và màu thanh máu và thanh năng lượng
const SDL_Color HPBG_COLOR = { 255, 0, 0, 255 };
const SDL_Color HP_COLOR = { 234, 164, 31, 255 };

const SDL_Color ENGBG_COLOR = { 155, 159, 191, 255 };
const SDL_Color ENG_COLOR = { 73, 222, 255, 255 };

constexpr const char* SASUKE_IMG_PATH = "assets/sasuke.png";
constexpr const char* AKAINU_IMG_PATH = "assets/akainu_stand.png";
constexpr const char* MADARA_IMG_PATH = "assets/madara.png";
constexpr const char* BOT_IMG_PATH = "assets/bot.png";
constexpr const char* BOSS_IMG_PATH = "assets/boss.png";

constexpr const char* imageTilePath = "assets/imageTileMap.png";
constexpr const char* tileMapPath = "assets/TileMap.txt";
constexpr const char* collisionImgPath = "assets/collisionImage.png";
constexpr const char* GENERAL_EFFECT_PATH = "assets/generalEffect.png";

constexpr const char* GAME_OVER_IMG = "assets/gameOver.png";
const int GAME_OVER_W = 784;
const int GAME_OVER_H = 379;

// Đường dẫn đoạn nhạc dài
constexpr const char* MUSIC_PATH = "assets/audio/background.mp3";

// Đường dẫn các đoạn âm ngắn
const std::vector<const char*> SOUND_PAHTS =
{
	"assets/audio/hurt.wav",					// 0
	"assets/audio/step3.wav",					
	"assets/audio/ping.wav",					// 2
	"assets/audio/select.wav",
	"assets/audio/teleport.wav",				// 4
	"assets/audio/jump.wav",
	"assets/audio/fire.wav",					// 6
	"assets/audio/chidori.wav",
	"assets/audio/chooseContinue.wav",			// 8
	"assets/audio/sharingan.wav",
	"assets/audio/ready.wav",					// 10
	"assets/audio/ko.wav",
	"assets/audio/gameover.wav",				// 12
	"assets/audio/hit.wav",
	"assets/audio/punch.wav"					// 14
};

const std::vector<const char*> MASKS = 
{
	"assets/fight/p1.png",
	"assets/fight/p2.png"
};

const int MASK_W = 39;
const int MASK_H = 55;

const int GENERAL_EFFECT_ID = -2;

const std::map<int, std::vector<int>> GENERAL_EFFECT = {
	{0,		{9, 120, 0, 0, 155, 153, 0, 0}}				// explosion
};

const std::map<int, std::vector<int>> SASUKE = {
	// state - f - s - x - y- w - h - costEnegy - damage
	{ -1,				{4, 150, 0,  0, 48, 75, 0, 0} },		// idle
	{ (int)SDLK_d,		{6, 110, 0, 75, 67, 75, 0, 0}},			// walk
	{ (int)SDLK_w,		{3, 200, 0, 150, 56, 75, 0, 0}},		// jump
	{ -2,				{1, 1, 0, 150, 56, 74, 0, 0} },			// fall
	{ (int)SDLK_c,		{1, 700, 0, 224, 58, 71, 0, 0}},			// thủ (đất)
	{ (int)SDLK_q,		{1, 700, 0, 296, 58, 74, 0, 0}},			// thủ (trên không)
	{ (int)SDLK_u,		{7, 120, 0, 371, 91, 75, 0, 15}},		// cận chiến
	{ (int)SDLK_e,      {3, 200, 0, 561, 107, 77, 0, 15}},		// cận chiến(bay)
	{ (int)SDLK_r,		{8, 100, 0, 446, 60, 77, 60, 0}},		// skill 1
	{ -3,				{7, 140, 242, 0, 86, 57, 0, 20} },		// effect 1
	{ (int)SDLK_t,      {3, 200, 0, 638, 62, 82, 60, 0}},		// skill 1 (bay)
	{-8,                {1, 1000, 471, 151, 46, 46, 0, 12}},	// effect 1 (bay)
	{ -4,				{3, 250, 450, 77, 57, 73, 0, 0} },		// get damage
	{ (int)SDLK_f,		{4, 200, 643, 83, 69, 67, 0, 0 } },		// dịch chuyển
	{ (int)SDLK_2,		{4, 250, 179, 150, 73, 72, 100, 0} },		// skill 2
	{ -5,				{5, 300, 0, 524, 171, 26, 0, 90}},		// effect 2.1
	{(int)SDLK_1,		{4, 250, 179, 150, 73, 72, 200, 0}},		// skill 3
	{-6,				{6, 300, 945, 0, 330, 255, 0, 150}},		// effect 3
	{-7,				{6, 170, 664, 327, 241, 196, 0, 0}},		// effect 2.2
	{0,                 {6, 140, 0, 720, 77, 73, 0, 0}}				// die
};

const std::map<int, std::vector<int>> AKAINU = {
	// state - f - s - x - y- w - h - hit - damage
		{-1,			{6, 150, 0, 0, 46, 80, 0, 0}},
		{(int)SDLK_u,	{9, 110, 0, 80, 88, 86, 0, 20}},
		{(int)SDLK_d,	{8, 150, 0, 166, 58, 77, 0, 0}},
		{(int)SDLK_w,	{3, 200, 0, 243, 68, 84, 0, 0}},
		{(int)SDLK_r,	{8, 150, 0, 327, 84, 77, 60, 0}},
		{-3,			{12, 140, 303, 0, 68, 78, 1, 20}},
		{-4,			{1, 1000, 492, 169, 63, 74, 0, 0}},
		{-2,			{1, 10, 806, 85, 84, 79, 0, 0}},
		{(int)SDLK_c,	{2, 450, 595, 165, 75, 78, 0, 0}},
		{(int)SDLK_q,	{2, 450, 753, 165, 76, 77, 0, 0}},
		{(int)SDLK_f,	{3, 180, 227, 257, 92, 70, 0, 0}},
		{0,             {4, 210, 0, 404, 78, 76, 0, 0}}
};

const std::map<int, std::vector<int>> MADARA = {
	// state - f - s - x - y- w - h - hit - damage
	{ -1,				{3, 150, 0,  0, 61, 89, 0, 0} },		// idle
	{ (int)SDLK_d,		{6, 110, 321, 0, 83, 89, 0, 0}},			// walk
	{ (int)SDLK_w,		{2, 250, 0, 89, 72, 92, 0, 0}},		// jump
	{ -2,				{1, 1, 0, 226, 74, 88, 0, 0} },			// fall
	{ (int)SDLK_c,		{1, 700, 1740, 94, 69, 89, 0, 0}},			// thủ (đất)
	//{ (int)SDLK_q,		{1, 1000, 0, 296, 58, 74, 0, 0}},			// thủ (trên không)
	{ (int)SDLK_u,		{5, 190, 819, 0, 127, 89, 0, 15}},		// cận chiến
	{(int)SDLK_e,       {4, 180, 0, 869, 97, 95, 0, 15}},		// cận chiến (bay)
	{ (int)SDLK_2,		{5, 400, 0, 314, 93, 112, 200, 0}},		// skill 2
	{ -3,				{6, 200, 0, 426, 525, 172, 1, 35} },		// effect 1
	{ -4,				{2, 340, 183, 2, 69, 87, 0, 0} },		// get damage
	{ (int)SDLK_f,		{4, 165, 1199, 89, 111, 95, 0, 0 } },		// dịch chuyển
	//{ (int)SDLK_1,		{7, 180, 0, 523, 298, 222, 0, 0} },		// skill 1
	{ -5,				{2, 1100, 733, 89, 233, 267, 0, 0}},		// effect 2.1
	{-7,				{3, 500, 0, 598, 187, 187, 1, 110}},		// effect 2.2
	{(int)SDLK_r,		{4, 400, 216, 89, 71, 91, 60, 0}},		// skill 1
	{ (int)SDLK_t,      {2, 200, 1454, 8, 82, 81, 60, 0}},		// skill 1 (bay)
	{-8,                {5, 200, 1618, 60, 29, 29, 0, 10}},	// effect 1 (bay)
	//{-6,				{6, 300, 945, 0, 330, 255, 0, 150}}		// effect 3
	{ 0,				{ 4, 210, 388, 869, 96, 95, 0, 0 }}
};

const std::map<int, std::vector<int>> BOT = {
	{0,		{1, 2000, 0, 0, 51, 91, 0, 0}},			// idle
	{1,		{6, 180, 51, 0, 51, 91, 0, 0}},			// walk
	{2,		{6, 180, 0, 91, 66, 73, 0, 0}},			// run
	{3,     {4, 200, 0, 164, 59, 86, 0, 10}},		// hit
	{4,     {4, 230, 236, 164, 59, 86, 0, 0}},		// throw weapon
	{5,     {2, 340, 357, 12, 66, 79, 0, 0}},		// hurt
	{6,     {9, 100, 0, 328, 30, 30, 0, 7}},		// weapon
	{7,     {3, 200, 0, 250, 88, 78, 0, 0}}			// die
};

const std::map<int, std::vector<int>> BOSS = {
	{0,		{1, 2000, 0, 0, 161, 272, 0, 0}},			// idle
	{1,		{6, 300, 0, 272, 193, 273, 0, 10}},			// walk
	{2,		{1, 300, 161, 0, 161, 272, 0, 0}},		// defend
	{3,     {7, 250, 0, 818, 255, 302, 0, 100}},		// hit
	{4,     {3, 1000, 0, 1120, 281, 278, 0, 0}},		// throw weapon
	{5,     {2, 550, 0, 545, 193, 273, 0, 0}},		// hurt
	{6,     {4, 300, 0, 1398, 64, 256, 0, 100}}		// weapon
};