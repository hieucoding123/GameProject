#pragma once

#include <vector>

class Animation
{
public:
	int frames;
	int speed;
	int srcX;
	int srcY;
	int w;
	int h;

	Animation() = default;
	Animation(std::vector<int> spriteInfo)
	{
		frames = spriteInfo[0];
		speed = spriteInfo[1];
		srcX = spriteInfo[2];
		srcY = spriteInfo[3];
		w = spriteInfo[4];
		h = spriteInfo[5];
	}
};