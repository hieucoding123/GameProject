#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "TransformComponent.h"

class SpriteComponent : public Component
{
public:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	SpriteComponent() = default;

	SpriteComponent(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			transform = &entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;

		srcRect.w = destRect.w = transform->width * transform->scale;
		srcRect.h = destRect.h = transform->high * transform->scale;

		destRect.x = destRect.y = 0;
	}

	void update() override
	{
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}
	
	void draw() override
	{
		TextureManager::Draw(texture, &srcRect, &destRect);
	}
};