#pragma once

#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
private:
	
public:
	Vector2D position;
	Vector2D velocity;
	int speed = 5;

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

		velocity.x = velocity.y = 0;
	}

	void init() override
	{
		/*position.x = 0.0f;
		position.y = 0.0f;*/
	}
	void update() override
	{

		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

		position.y += GRAVITY;

		if (position.x <= 0) position.x = 0;
		if (position.y + high >= (GROUND * MAP_SCALE))
		{
			position.y = (GROUND * MAP_SCALE) - high;
			entity->onGround = true;
		}
	}
};