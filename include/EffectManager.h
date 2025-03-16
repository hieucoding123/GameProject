#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include "Effect.h"
#include "Components/Attribute.h"

class EffectManager
{
public:
	EffectManager() = default;

	/*
	* Thêm effect mới
	* @param e Con trỏ unique tới effect muốn thêm
	*/
	void addEffect(std::unique_ptr<Effect> e);

	void update();
	void draw();
	/*
	* Kiểm tra va chạm giữa effect và một thực thể sống trong game
	* @param attrib Thuộc tính của thực thể
	* @param rect Hình chữ nhật chứa thực thể
	*/
	void checkVar(Attribute* attrib, SDL_Rect* rect);
private:
	std::vector<std::unique_ptr<Effect>> effects;
};