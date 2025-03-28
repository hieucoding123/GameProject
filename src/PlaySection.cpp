﻿#include "PlaySection.h"
#include "GameObjects/Sasuke.h"
#include "GameObjects/Akainu.h"
#include "GameObjects/Madara.h"
#include "GameObjects/Tile.h"
#include "Game.h"
#include "Map.h"
#include "Const.h"
#include <algorithm>

std::vector<std::unique_ptr<Tile>> PlaySection::tiles;
EffectManager PlaySection::effectManager;
int PlaySection::MAP_SCALE = 2;
SDL_Rect PlaySection::camera = { 0, 0, WIDTH, HIGH };
std::vector<GameObject*> PlaySection::gameObjects;

Map* map;

PlaySection::PlaySection()
{

}

PlaySection::~PlaySection()
{

}

void PlaySection::playLoad()
{
	std::vector<std::unique_ptr<Tile>> tiles;
	EffectManager effectManager;
	MAP_SCALE = 2;
	SDL_Rect camera = { 0, 0, WIDTH, HIGH };
	std::vector<GameObject*> gameObjects;
}

void PlaySection::init(std::vector<int> ID)
{
	// đặt camera ở giữa
	camera.x = (WIDTH * MAP_SCALE - WIDTH) / 2;
	camera.y = (HIGH * MAP_SCALE - HIGH);

	// Khởi tạo map
	map = new Map;
	map->LoadMap(tileMapPath);

	// Khởi tạo nhân vật
	gameObjects.push_back(new GameObject);
	setCharacter(ID[0], camera.x + 100, GROUND * MAP_SCALE, true);
	gameObjects.push_back(new GameObject);
	setCharacter(ID[1], camera.x + camera.w - 100, GROUND * MAP_SCALE, true);

	isPlaying = true;

	// Dọn dẹp các hiệu ứng từ ván trước
	effectManager.clean();
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
	for (auto& t : tiles)
	{
		t->update();
	}
	gameObjects[0]->update();
	gameObjects[0]->ADWSController();
	gameObjects[1]->update();
	gameObjects[1]->LRUDController();

	// Cập nhật kết thúc
	if (gameObjects[0]->getHP() <= 0 || gameObjects[1]->getHP() <= 0)
	{
		isPlaying = false;
	}

	effectManager.update();
}

void PlaySection::render()
{
	// Phần vẽ game
	SDL_RenderClear(Game::renderer);

	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& object : gameObjects)
	{
		object->draw();
	}

	TextureManager::DrawHP(SELECT_W, 0, (gameObjects[0]->getHP() * HP_W) / HP, HPBG_COLOR, HP_COLOR);
	TextureManager::DrawEnergy(SELECT_W, HP_H,
		(gameObjects[0]->getEnergy() * (HP_W - 20)) / ENERGY, ENGBG_COLOR, ENG_COLOR);

	TextureManager::DrawHP(camera.w - HP_W - SELECT_W, 0,
		((HP - gameObjects[1]->getHP()) * HP_W) / HP, HP_COLOR, HPBG_COLOR);
	TextureManager::DrawEnergy(camera.w - HP_W - SELECT_W + 20, HP_H,
		((ENERGY - gameObjects[1]->getEnergy()) * (HP_W - 20)) / ENERGY, ENG_COLOR, ENGBG_COLOR);
	
	effectManager.draw();

	SDL_RenderPresent(Game::renderer);
}

void PlaySection::clean()
{
	// Hủy các thành phần trong phần chơi

	effectManager.clean();
	gameObjects.clear();
	delete map;
	map = nullptr;
}

void PlaySection::setCharacter(const int& ID, int xpos, int ypos, bool camera)
{
	// Cài đặt và khởi tạo nhân vật qua ID

	switch (ID)
	{
	case PLAYER1ID:
	{
		gameObjects[gameObjects.size() - 1] = new Sasuke;
		gameObjects[gameObjects.size() - 1]->init();
		gameObjects[gameObjects.size() - 1]->setPosition(xpos, ypos);
		if (camera) gameObjects[gameObjects.size() - 1]->setCamera();
		break;
	}
	case PLAYER2ID:
	{
		gameObjects[gameObjects.size() - 1] = new Akainu;
		gameObjects[gameObjects.size() - 1]->init();
		gameObjects[gameObjects.size() - 1]->setPosition(xpos, ypos);
		if (camera) gameObjects[gameObjects.size() - 1]->setCamera();
		break;
	}
	case PLAYER3ID:
	{
		gameObjects[gameObjects.size() - 1] = new Madara;
		gameObjects[gameObjects.size() - 1]->init();
		gameObjects[gameObjects.size() - 1]->setPosition(xpos, ypos);
		if (camera) gameObjects[gameObjects.size() - 1]->setCamera();
		break;
	}
	}
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
			return (obj->hasCamera() && ((obj->getXpos() - camera.x < x) ||
				(obj->getXpos() + obj->getWidth() - camera.x - camera.w > x)));
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
			return (obj->hasCamera() && ((obj->getYpos() - camera.y < y) ||
				(obj->getYpos() + obj->getHigh() - camera.y - camera.h > y)));
		});

	if (it == gameObjects.end())
	{
		camera.y += y;
	}
}