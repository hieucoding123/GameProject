#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include <vector>

class Effect
{
public:
	Effect();
	/*
	* @param texture texture của hiệu ứng
	* @param id id của hiệu ứng
	* @param v thông tin về vị trí lấy hiệu ứng trên ảnh
	* @param vX vận tốc X
	* @param vY vận tốc Y
	* @param scl tỉ lệ
	* @param f lật ảnh
	* @param xpos vị trí khởi tạo trên trục X
	* @param ypos vị trí khởi tạo trên trục Y
	*/
	Effect(SDL_Texture* texture, int id, const std::vector<int>& v, int vX, int vY,
		int scl, SDL_RendererFlip f, int xpos, int ypos);
	void update();
	void draw();
	bool isActive() const { return active; }
	SDL_Rect getRect() const;
	int getDamage() const;
	/*
	* vô hiệu hóa sát thương
	*/
	void disableDamage() { damage = 0; }
	int getID() const;
private:
	SDL_Texture* effectTexture;
	SDL_Rect srcRect, destRect;
	SDL_RendererFlip effectFlip;
	int frames;
	int speed;
	int damage;
	int vx, vy;
	int realX, realY;

	Uint32 lastUpdate;
	bool active = false;
	int currentFrame;
	int ID;					// ID xác định đối tượng tạo ra hiệu ứng
};