#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "TransformComponent.h"
#include "Animation.h"
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

	int frames = 4;		// số khung hình
	int speed = 150;	// tốc độ

	Uint32 lastUpdate;
	int currentFrame;
public:
	int ID = getID();
	const char* state;	// trạng thái
	bool onGround;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;	// lật bản vẽ

	std::map<const char*, Animation> animations;	// thông tin hoạt ảnh

	//SpriteComponent() = default;

	SpriteComponent(const char* path, bool isAnimated)
	{
		texture = TextureManager::LoadTexture(path);

		animated = isAnimated;
		loadAnimations(GAMECHARACTERS.at(ID));
		
		use("idle");
		/*lastUpdate = SDL_GetTicks();
		currentFrame = 0;*/
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
		lastUpdate = SDL_GetTicks();
		currentFrame = 0;
	}

	void update() override
	{
		if (animated)
		{
			Uint32 now = SDL_GetTicks();
			if (now - lastUpdate > speed) {
				currentFrame++; 
				lastUpdate = now;

				if (currentFrame >= frames) {
					if (state != "run")
					{
						use("idle");
						transform->velocity.x = 0;
						transform->velocity.y = 0;
					}
					else
					{
						currentFrame = 0;	// nếu đang chạy -> chạy tiếp
					}
				}
			}
		}

		srcRect.x = currentFrame * srcRect.w;

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

		lastUpdate = SDL_GetTicks();		// đặt lại tgian
		currentFrame = 0;
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