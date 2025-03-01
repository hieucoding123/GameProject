#pragma once

#include <vector>

class Animation
{
public:
	int frames;
	int speed;

	// thông số khung hình gốc
	int srcX;
	int srcY;
	int w;
	int h;
	bool hit;
	int damage;

	Animation() = default;
	Animation(std::vector<int> spriteInfo)
	{
		frames = spriteInfo[0];
		speed = spriteInfo[1];
		srcX = spriteInfo[2];
		srcY = spriteInfo[3];
		w = spriteInfo[4];
		h = spriteInfo[5];
		hit = spriteInfo[6];
		damage = spriteInfo[7];
	}
};