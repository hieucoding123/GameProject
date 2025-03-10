#pragma once

#include "AnimationComponent.h"

class ADWSKeyboard : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	AnimationComponent* animations;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		sprite = &entity->getComponent<SpriteComponent>();

		animations = &entity->getComponent<AnimationComponent>();
	}

	void update() override
	{
		// khi nhấn phím xuống
		if (Game::event.type == SDL_KEYDOWN)
		{
			// khi đang đứng yên hoặc chạy
			if (animations->animFinished)
			{
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_w:
					animations->animFinished = false;
					transform->velocity.y = -3;
					animations->use("jump");
					break;
				case SDLK_d:
					transform->velocity.x = 1;
					sprite->spriteFlip = SDL_FLIP_NONE;
					animations->animFinished = true;		// sẵn sàng nhận phím tiếp theo
					animations->use("run");
					break;
				case SDLK_a:
					transform->velocity.x = -1;
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					animations->animFinished = true;		// sẵn sàng nhận phím tiếp theo
					animations->use("run");
					break;
				case SDLK_u:
					transform->velocity.x = 0;
					animations->use("attackcb");
					animations->animFinished = false;
					break;
				case SDLK_r:
					transform->velocity.x = 0;
					animations->use("skill1");
					animations->animFinished = false;
					sprite->effect = Effect(GAMECHARACTERS.at(sprite->ID).at("eff1"), 9, 0, transform->scale, sprite->spriteFlip,
						entity->getRect().x + entity->getRect().w * sprite->ROL, entity->getRect().y);
					break;
				default:
					break;
				}
			}
		}

		if (Game::event.type == SDL_KEYUP)
		{
			
		}
	}
};