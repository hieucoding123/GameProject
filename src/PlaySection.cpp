﻿#include "PlaySection.h"
#include "GameObjects/Sasuke.h"
#include "GameObjects/Akainu.h"
#include "GameObjects/Madara.h"
#include "GameObjects/Bot.h"
#include "GameObjects/Boss.h"
#include "GameObjects/Tile.h"
#include "Game.h"
#include "Map.h"
#include "Const.h"
#include <algorithm>

EffectManager PlaySection::effectManager;
int PlaySection::MAP_SCALE = 2;
SDL_Rect PlaySection::camera = { 0, 0, WIDTH, HIGH };
std::vector<GameObject*> PlaySection::gameObjects;
std::vector<GameObject*> PlaySection::bots;

Map* map;

PlaySection::PlaySection()
{

}

PlaySection::~PlaySection()
{

}

void PlaySection::playLoad()
{
	EffectManager effectManager;
	MAP_SCALE = 2;
	SDL_Rect camera = { 0, 0, WIDTH, HIGH };
	std::vector<GameObject*> gameObjects;
	std::vector<Bot*> bots;
}

void PlaySection::init(std::vector<int> ID, const int& m)
{
	id = ID;
	mode = m;
	players = ID.size();

	// đặt camera ở giữa
	camera.x = (WIDTH * MAP_SCALE - WIDTH) / 2;
	camera.y = (HIGH * MAP_SCALE - HIGH);

	// Khởi tạo map
	map = new Map;
	map->LoadMap(tileMapPath);

	// Khởi tạo nhân vật, mode
	if (mode == 1) survivalModeInit();

	if (players == 1) onePlayerInit();
	else twoPlayersInit();

	isPlaying = true;

	// Dọn dẹp các hiệu ứng từ ván trước (nếu có)
	effectManager.clean();

	// phát đoạn nhạc sẵn sàng
	Game::playSound(10);
}

void PlaySection::handleEvents()
{
	SDL_PollEvent(&Game::event);
	// Xử lý sự kiện
	switch (Game::event.type)
	{
	case SDL_QUIT:
		isPlaying = false;
		break;
	default:
		break;
	}
}

void PlaySection::update()
{
	// Phần cập nhật game
	map->update();
	
	if (players == 1) onePlayerUpdate();
	else twoPlayersUpdate();

	// Cập nhật kết thúc
	if (mode == 0) soloModeUpdate();
	else survivalModeUpdate();

	effectManager.update();
}

void PlaySection::render()
{
	// Phần vẽ game
	SDL_RenderClear(Game::renderer);

	map->draw();

	for (auto& object : gameObjects)
	{
		object->draw();
	}

	for (auto& bot : bots)
	{
		bot->draw();
	}
	
	if (players == 1) onePlayerDraw();
	else twoPlayersDraw();
		
	effectManager.draw();

	SDL_RenderPresent(Game::renderer);
}

void PlaySection::clean()
{
	// Hủy các thành phần trong phần chơi
	
	effectManager.clean();
	gameObjects.clear();
	bots.clear();
	map->clean();
	delete map;
	map = nullptr;
	SDL_DestroyTexture(p1Texture);
	SDL_DestroyTexture(p2Texture);
}

void PlaySection::setCharacter(const int& ID, int xpos, int ypos)
{
	// Cài đặt và khởi tạo nhân vật qua ID

	switch (ID)
	{
	case PLAYER1ID:
	{
		gameObjects[gameObjects.size() - 1] = new Sasuke;
		break;
	}
	case PLAYER2ID:
	{
		gameObjects[gameObjects.size() - 1] = new Akainu;
		break;
	}
	case PLAYER3ID:
	{
		gameObjects[gameObjects.size() - 1] = new Madara;
		break;
	}
	}
	gameObjects[gameObjects.size() - 1]->init();
	gameObjects[gameObjects.size() - 1]->setPosition(xpos, ypos);
}

bool PlaySection::AABB(const SDL_Rect& rec1, const SDL_Rect& rec2)
{
	// Kiểm tra hai hình chữ nhật giao nhau
	if (rec1.x + rec1.w >= rec2.x &&
		rec2.x + rec2.w >= rec1.x &&
		rec1.y + rec1.h >= rec2.y &&
		rec2.y + rec2.h >= rec1.y)
	{
		return true;
	}
	return false;
}

void PlaySection::setCameraX(int x)
{
	// Tìm đối tượng có gắn camera và bị mất hình khi chỉnh camera
	auto it = std::find_if(gameObjects.begin(), gameObjects.end(),
		[x](const GameObject* obj) {
			return ((obj->getXpos() - camera.x < x) ||
				(obj->getXpos() + obj->getWidth() - camera.x - camera.w > x));
		});

	// Không có đối tượng vi phạm
	if (it == gameObjects.end())
	{
		camera.x += x;
	}
}

void PlaySection::setCameraY(int y)
{
	auto it = find_if(gameObjects.begin(), gameObjects.end(),
		[y](const GameObject* obj) {
			return ((obj->getYpos() - camera.y < y) ||
				(obj->getYpos() + obj->getHigh() - camera.y - camera.h > y));
		});

	if (it == gameObjects.end())
	{
		camera.y += y;
	}
}

void PlaySection::survivalModeInit()
{
	int randomXPos;
	randomXPos = rand() % (WIDTH * MAP_SCALE);
	Boss* boss = new Boss;
	boss->init();
	boss->setPosition(randomXPos, GROUND * MAP_SCALE);
	bots.push_back(boss);
	for (int i = 0; i < MAX_BOT - 1; i++)
	{
		randomXPos = rand() % (WIDTH * MAP_SCALE);
		Bot* bot = new Bot;
		bot->init();
		bot->setPosition(rand() % WIDTH * MAP_SCALE, GROUND * MAP_SCALE);
		bots.push_back(bot);
	}
}

void PlaySection::soloModeUpdate()
{
	if (gameObjects[0]->isDie() || gameObjects[1]->isDie())
		isPlaying = false;
}

void PlaySection::survivalModeUpdate()
{
	switch (players)
	{
	case 1:
		if (gameObjects[0]->isDie())
			isPlaying = false;
		break;
	case 2:
		if (gameObjects[0]->isDie() && gameObjects[1]->isDie())
			isPlaying = false;
		break;
	default:
		break;
	}

	for (auto& bot : bots)
		bot->update();
	// boss bị tiêu diệt
	if (bots[0]->isDie())
	{
		isPlaying = false;
	}

	bots.erase(std::remove_if(std::begin(bots), std::end(bots),
		[](const GameObject* bot)
		{
			return bot->isDie();
		}), std::end(bots));

	for (int i = 0; i < MAX_BOT - bots.size(); i++)
	{
		Bot* bot = new Bot;
		bot->init();
		int randomXPos = rand() % camera.w + camera.x;
		bot->setPosition(randomXPos, GROUND * MAP_SCALE);
		bots.push_back(bot);
	}
}

void PlaySection::onePlayerInit()
{
	gameObjects.push_back(new GameObject);
	setCharacter(id[0], camera.x + camera.w / 2, GROUND * MAP_SCALE);

	p1Texture = TextureManager::LoadTexture(MASKS[0]);

	destRect1.w = MASK_W;
	destRect1.h = MASK_H;
}

void PlaySection::onePlayerUpdate()
{
	gameObjects[0]->update();
	gameObjects[0]->ADWSController();

	// Camera đi theo 1 nhân vật
	camera.x = gameObjects[0]->getXpos() - camera.w / 2;
	if (camera.x < 0) camera.x = 0;
	if (camera.x + camera.w >= WIDTH * MAP_SCALE) camera.x = WIDTH * MAP_SCALE - camera.w;

	destRect1.x = gameObjects[0]->getXpos() - camera.x + (gameObjects[0]->getWidth() - destRect1.w) / 2;
	destRect1.y = gameObjects[0]->getYpos() - destRect1.h - camera.y;
}

void PlaySection::onePlayerDraw()
{
	TextureManager::DrawHP(SELECT_W, 0, (gameObjects[0]->getHP() * HP_W) / HP, HP_H, HP_W, HPBG_COLOR, HP_COLOR);
	TextureManager::DrawEnergy(SELECT_W, HP_H,
		(gameObjects[0]->getEnergy() * (HP_W - 20)) / ENERGY, HP_H, HP_W, ENGBG_COLOR, ENG_COLOR);

	TextureManager::Draw(p1Texture, NULL, &destRect1, SDL_FLIP_NONE);
}

void PlaySection::twoPlayersInit()
{
	gameObjects.push_back(new GameObject);
	setCharacter(id[0], camera.x + 100, GROUND * MAP_SCALE);
	gameObjects.push_back(new GameObject);
	setCharacter(id[1], camera.x + camera.w - 100, GROUND * MAP_SCALE);

	p1Texture = TextureManager::LoadTexture(MASKS[0]);
	p2Texture = TextureManager::LoadTexture(MASKS[1]);

	destRect1.w = destRect2.w = MASK_W;
	destRect1.h = destRect2.h = MASK_H;
}

void PlaySection::twoPlayersUpdate()
{
	gameObjects[0]->update();
	gameObjects[0]->ADWSController();

	gameObjects[1]->update();
	gameObjects[1]->LRUDController();

	destRect1.x = gameObjects[0]->getXpos() - camera.x + (gameObjects[0]->getWidth() - destRect1.w) / 2;
	destRect1.y = gameObjects[0]->getYpos() - destRect1.h - camera.y;

	destRect2.x = gameObjects[1]->getXpos() - camera.x + (gameObjects[1]->getWidth() - destRect1.w) / 2;
	destRect2.y = gameObjects[1]->getYpos() - destRect2.h - camera.y;

}

void PlaySection::twoPlayersDraw()
{
	TextureManager::DrawHP(SELECT_W, 0, (gameObjects[0]->getHP() * HP_W) / HP, HP_H, HP_W, HPBG_COLOR, HP_COLOR);
	TextureManager::DrawEnergy(SELECT_W, HP_H,
		(gameObjects[0]->getEnergy() * (HP_W - 20)) / ENERGY, HP_H, HP_W, ENGBG_COLOR, ENG_COLOR);

	TextureManager::Draw(p1Texture, NULL, &destRect1, SDL_FLIP_NONE);

	TextureManager::DrawHP(camera.w - HP_W - SELECT_W, 0,
		((HP - gameObjects[1]->getHP()) * HP_W) / HP, HP_H, HP_W, HP_COLOR, HPBG_COLOR);
	TextureManager::DrawEnergy(camera.w - HP_W - SELECT_W + 20, HP_H,
		((ENERGY - gameObjects[1]->getEnergy()) * (HP_W - 20)) / ENERGY, HP_H, HP_W, ENG_COLOR, ENGBG_COLOR);

	TextureManager::Draw(p2Texture, NULL, &destRect2, SDL_FLIP_NONE);
}