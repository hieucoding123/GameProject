#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "TransformComponent.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;		

	bool animated;
	const char* state;	// trạng thái

	int frames = 4;		// số khung hình
	int speed = 150;	// tốc độ

public:
	std::map<const char*, Animation> animations;	// thông tin hoạt ảnh

	//SpriteComponent() = default;

	SpriteComponent(const char* path, bool isAnimated)
	{
		texture = TextureManager::LoadTexture(path);

		animated = isAnimated;
		Animation idle = Animation(SASUKE[0]);
		animations.emplace("idle", idle);		// đứng yên
		
		use("idle");
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
		if (animated)
		{
			srcRect.x = ((SDL_GetTicks() / speed) % frames) * srcRect.w;
		}

		srcRect.y = animations[state].srcY;

		// cập nhật theo trạng thái
		transform->high = animations[state].h;
		transform->width = animations[state].w;

		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->high * transform->scale;
	}
	
	void draw() override
	{
		TextureManager::Draw(texture, &srcRect, &destRect);
	}

	// sử dụng hoạt ảnh
	void use(const char* animation)
	{
		state = animation;
		frames = animations[animation].frames;
		speed = animations[animation].speed;
		srcRect.w = animations[animation].w;
		srcRect.h = animations[animation].h;
	}
};