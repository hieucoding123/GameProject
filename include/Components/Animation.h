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
	
	/*
	* Tùy chỉnh trạng thái thành công
	* @param s trạng thái(key) có trong map dữ liệu hành động
	* @return true nếu thành công
	*/
	bool setStateSuccess(int s);
	
	/*
	* Kiểm tra hành động đã kết thúc chưa
	* @return true nếu hành động đã kết thúc
	*/
	bool isFinished() const { return animFinished; }
	
	/*
	* Tùy chỉnh kết thúc hành động
	* @param b true nếu đặt hành động kết thúc
	*/
	void setFinished(bool b);

	/*
	* Lấy thông tin hiệu ứng
	* @param key key trong map dữ liệu hành động
	* @return 1 vector chứa thông tin để khởi tạo hiệu ứng
	*/
	std::vector<int> getEffectInfor(int key);
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