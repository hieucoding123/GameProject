#pragma once

#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
private:
	
public:
	Vector2D position;
	int high = 64;
	int width = 32;
	int scale = 2;
	TransformComponent()
	{
		/*position.x = 0.0f;
		position.y = 0.0f;*/
	}
	TransformComponent(float xpos, float ypos, int w, int h, int s)
	{
		position.x = xpos;
		position.y = ypos;
		high = h;
		width = w;
		scale = s;
	}
	TransformComponent(float xpos, float ypos)
	{
		position.x = xpos;
		position.y = ypos;
	}

	void init() override
	{
		/*position.x = 0.0f;
		position.y = 0.0f;*/
	}
	void update() override
	{

	}
};