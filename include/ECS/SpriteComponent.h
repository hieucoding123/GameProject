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
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;	// lật bản vẽ

	std::map<const char*, Animation> animations;	// thông tin hoạt ảnh

	//SpriteComponent() = default;

	SpriteComponent(const char* path, bool isAnimated)
	{
		texture = TextureManager::LoadTexture(path);

		animated = isAnimated;
		loadAnimations(SASUKE);
		
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

		// cập nhật vị trí lấy sprite sheet
		srcRect.y = animations[state].srcY;

		// cập nhật theo trạng thái
		transform->high = animations[state].h;
		transform->width = animations[state].w;

		destRect.x = (int)transform->position.x - Game::camera.x;
		destRect.y = (int)transform->position.y - Game::camera.y;

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->high * transform->scale;
	}
	
	void draw() override
	{
		TextureManager::Draw(texture, &srcRect, &destRect, spriteFlip);
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

	// tải các hoạt ảnh
	void loadAnimations(const std::map<const char*, std::vector<int>>& aniInfor)
	{
		for (const auto& pair : aniInfor)
		{
			animations.emplace(pair.first, Animation(pair.second));
		}
	}
};