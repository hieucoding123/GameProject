#pragma once

#include "SpriteComponent.h"

class ColliderComponent : public Component
{
private:
	SpriteComponent* sprite;
public:
	SDL_Rect rect;
	SDL_Rect attackBox;
	ColliderComponent() = default;

	void init() override
	{
		if (!entity->hasComponent<SpriteComponent>())
		{
			sprite = &entity->addComponent<SpriteComponent>();
		}
		sprite = &entity->getComponent<SpriteComponent>();

		rect = sprite->getDestRect();

		attackBox.x = rect.x + rect.w * 4.0 / 5;
		attackBox.y = rect.y;
		attackBox.h = rect.h;
		attackBox.w = rect.w * 1.0 / 5;
		
	}

	void update() override
	{
		rect = sprite->getDestRect();
		if (sprite->spriteFlip == SDL_FLIP_NONE)
			attackBox.x = rect.x + rect.w * 4.0 / 5;
		else if (sprite->spriteFlip == SDL_FLIP_HORIZONTAL)
			attackBox.x = rect.x;

		attackBox.y = rect.y;
		attackBox.h = rect.h;
		attackBox.w = rect.w * 1.0 / 5;
	}
};