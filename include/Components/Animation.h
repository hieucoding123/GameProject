#pragma once

#include "SDL.h"
#include <map>
#include <vector>
#include "Vector2D.h"
#include "Attribute.h"

class Animation
{
public:
	Animation(Attribute* attribute, Vector2D* vel,
		SDL_Rect* rect, const std::map<int, std::vector<int>>& FIGURE);
	void setState(int s);										// đặt trạng thái
	bool isFinished() const { return animFinished; }			// kiểm tra kết thúc
	void setFinished(bool b);									// cho kết thúc
	std::vector<int> getEffectInfor(int state);					// lấy thông tin hiệu ứng
	void update();
	~Animation();
private:
	SDL_Rect* srcRect;
	Attribute* attrib;
	Vector2D* velocity;
	int frames = 4;		// số khung hình
	int speed = 150;	// tốc độ

	Uint32 lastUpdate;
	int currentFrame;

	bool animFinished;

	std::map<int, std::vector<int>> figure;
};