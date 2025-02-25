#pragma once

#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
private:
	
public:
	Vector2D position;
	int high;
	int width;
	int scale;
	TransformComponent()
	{
		position.x = 0;
		position.y = 0;
	}
	TransformComponent(float xpos, float ypos)
	{
		position.x = xpos;
		position.y = ypos;
	}

	void init() override
	{
		position.x = 0;
		position.y = 0;
	}
	void update() override
	{

	}
};