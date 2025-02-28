#pragma once

#include "TransformComponent.h"
#include "SpriteComponent.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	// lưu sdl_flip hiện tại
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		// khi nhấn phím xuống
		if (Game::event.type == SDL_KEYDOWN)
		{
			if (sprite->ID == PLAYER1ID)
			{
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_w:
					transform->velocity.y = -1;
					break;
				case SDLK_d:
					transform->velocity.x = 1;
					sprite->spriteFlip = SDL_FLIP_NONE;
					sprite->use("run");
					break;
				case SDLK_a:
					transform->velocity.x = -1;
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					sprite->use("run");
					break;
				case SDLK_u:
					transform->velocity.x = 0;
					sprite->use("attackcb");
					break;
				default:
					break;
				}
				// cập nhật hiện tại
				flip = sprite->spriteFlip;
			}
		}

		if (Game::event.type == SDL_KEYUP && sprite->state == "idle")
		{
				/*transform->velocity.y = 0;
				transform->velocity.x = 0;*/
			
			//switch (Game::event.key.keysym.sym)
			//{
			//case SDLK_w:
			//	transform->velocity.y = 0;
			//	sprite->use("idle");
			//	break;
			//case SDLK_a:
			//	transform->velocity.x = 0;
			//	sprite->spriteFlip = flip;		// nhân vật giữ yên hướng vẽ
			//	sprite->use("idle");
			//	break;
			//case SDLK_d:
			//	transform->velocity.x = 0;
			//	sprite->spriteFlip = flip;
			//	sprite->use("idle");
			//	break;
			//case SDLK_u:
			//	transform->velocity.x = 0;
			//	sprite->use("idle");
			//	break;
			//default:
			//	break;
			//}
		}
	}
};