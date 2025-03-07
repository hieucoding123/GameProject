#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "TransformComponent.h"

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

	// đánh dấu
	SDL_Texture* maskTexture;
	SDL_Rect mSrcRect, mDestRect;
	bool animated;
public:
	int ID = getID();
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;	// lật bản vẽ
	int ROL;
	Effect effect;

	SpriteComponent() = default;

	SpriteComponent(const char* path, bool isAnimated)
	{
		texture = TextureManager::LoadTexture(path);
		maskTexture = TextureManager::LoadTexture(MASKS[ID - 1]);

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

		mSrcRect.x = mSrcRect.y = 0;
		mSrcRect.w = MASK_W;
		mSrcRect.h = MASK_H;
	}

	void update() override
	{
		// theo camera
		destRect.x = (int)transform->position.x - Game::camera.x;
		destRect.y = (int)transform->position.y - Game::camera.y;

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->high * transform->scale;
		
		mDestRect.w = transform->scale * MASK_W * 1.0 / 2;
		mDestRect.h = transform->scale * MASK_H * 1.0 / 2;
		mDestRect.x = (destRect.x + (destRect.w - mDestRect.w) * 1.0 / 2);
		mDestRect.y = (destRect.y - mDestRect.h);
		ROL = ((int)spriteFlip * -2 + 1);

		effect.update();
	}

	SDL_Rect getDestRect() const
	{
		return destRect;
	}
	
	void draw() override
	{
		TextureManager::Draw(texture, &srcRect, &destRect, spriteFlip);
		TextureManager::Draw(maskTexture, &mSrcRect, &mDestRect, SDL_FLIP_NONE);
		if (effect.isActive())
		{
			TextureManager::Draw(texture, &effect.srcRect, &effect.destRect, spriteFlip);
		}
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