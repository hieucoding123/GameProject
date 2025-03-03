#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "TransformComponent.h"
#include <map>

// lấy id của nhân vật
inline int getID()
{
	static int ID = 1;
	return ID++;
}

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;		
	bool animated;
public:
	int ID = getID();

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;	// lật bản vẽ

	SpriteComponent() = default;

	SpriteComponent(const char* path, bool isAnimated)
	{
		texture = TextureManager::LoadTexture(path);

		animated = isAnimated;
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			transform = &entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->high;

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->high * transform->scale;

		destRect.x = destRect.y = 0;
	}

	void update() override
	{
		// theo camera
		destRect.x = (int)transform->position.x - Game::camera.x;
		destRect.y = (int)transform->position.y - Game::camera.y;

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->high * transform->scale;
	}

	SDL_Rect getDestRect() const
	{
		return destRect;
	}
	
	void draw() override
	{
		TextureManager::Draw(texture, &srcRect, &destRect, spriteFlip);
	}

	bool isAnimated() const { return animated; }

	void setSrcW(int w)
	{
		srcRect.w = w;
	}
	void setSrcH(int h)
	{
		srcRect.h = h;
	}
	void setSrcX(int x)
	{
		srcRect.x = x;
	}
	void setSrcY(int y)
	{
		srcRect.y = y;
	}
	void setDestH(int h)
	{
		destRect.h = h;
	}
	void setDestW(int w)
	{
		destRect.w = w;
	}
};