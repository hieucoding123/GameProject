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
	SDL_Rect srcRect;

	// đánh dấu
	SDL_Texture* maskTexture;
	SDL_Rect mSrcRect, mDestRect;
	bool animated;
public:
	int ID = getID();
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;	// lật bản vẽ
	int ROL;										// quay trái hoặc phải
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

		entity->Rect()->w = transform->width * transform->scale;
		entity->Rect()->h = transform->high * transform->scale;

		entity->Rect()->x = 0;
		entity->Rect()->y = 0;

		mSrcRect.x = mSrcRect.y = 0;
		mSrcRect.w = MASK_W;
		mSrcRect.h = MASK_H;

		Game::effects.push_back(&effect);

	}

	void update() override
	{
		// theo camera
		entity->Rect()->x = (int)transform->position.x - Game::camera.x;
		entity->Rect()->y = (int)transform->position.y - Game::camera.y;

		entity->Rect()->w = transform->width * transform->scale;
		entity->Rect()->h = transform->high * transform->scale;
		
		mDestRect.w = transform->scale * MASK_W * 1.0 / 2;
		mDestRect.h = transform->scale * MASK_H * 1.0 / 2;
		mDestRect.x = (entity->getRect().x + (entity->getRect().w - mDestRect.w) * 1.0 / 2);
		mDestRect.y = (entity->getRect().y - mDestRect.h);
		ROL = ((int)spriteFlip * -2 + 1);

		effect.update();
	}
	
	void draw() override
	{
		TextureManager::Draw(texture, &srcRect, entity->Rect(), spriteFlip);
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
	// tăng src.x, chạy hoạt hình 
	void addSrcX(int n)
	{
		srcRect.x += n;
	}
};