#pragma once

#include "TransformComponent.h"
#include "SpriteComponent.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

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
			// khi đang đứng yên hoặc chạy
			if (sprite->ID == PLAYER1ID && sprite->animFinished)
			{
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_w:
					transform->velocity.y = -1;
					sprite->animFinished = false;
					break;
				case SDLK_d:
					transform->velocity.x = 1;
					sprite->spriteFlip = SDL_FLIP_NONE;
					sprite->animFinished = true;		// sẵn sàng nhận phím tiếp theo
					sprite->use("run");
					break;
				case SDLK_a:
					transform->velocity.x = -1;
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					sprite->animFinished = true;		// sẵn sàng nhận phím tiếp theo
					sprite->use("run");
					break;
				case SDLK_u:
					transform->velocity.x = 0;
					sprite->use("attackcb");
					entity->attrib.isHitting = true;			// đang đánh
					sprite->animFinished = false;
					break;
				default:
					break;
				}
				
			}
			else if (sprite->ID == PLAYER2ID && sprite->animFinished)
			{
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_UP:
					transform->velocity.y = -1;
					sprite->animFinished = false;
					break;
				case SDLK_RIGHT:
					transform->velocity.x = 0.5;
					sprite->spriteFlip = SDL_FLIP_NONE;
					sprite->animFinished = true;		// sẵn sàng nhận phím tiếp theo
					sprite->use("run");
					break;
				case SDLK_LEFT:
					transform->velocity.x = -0.5;
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					sprite->animFinished = true;		// sẵn sàng nhận phím tiếp theo
					sprite->use("run");
					break;
				case SDLK_1:
					transform->velocity.x = 0;
					sprite->use("attackcb");
					entity->attrib.isHitting = true;			// đang đánh
					sprite->animFinished = false;
					break;
				default:
					break;
				}
			}
		}

		if (Game::event.type == SDL_KEYUP)
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