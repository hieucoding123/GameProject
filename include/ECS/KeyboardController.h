#pragma once

#include "AnimationComponent.h"

class KeyboardController : public Component
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
			if (sprite->ID == PLAYER1ID && animations->animFinished)
			{
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_w:
					animations->animFinished = false;
					entity->attrib.isHitting = false;
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
					entity->attrib.isHitting = true;			// đang đánh
					animations->animFinished = false;
					break;
				case SDLK_r:
					transform->velocity.x = 0;
					animations->use("skill1");
					entity->attrib.isHitting = true;			// đang đánh
					animations->animFinished = false;
					break;
				case SDLK_f:
					transform->velocity.x = 1.5 * ((int)sprite->spriteFlip * -2 + 1);
					animations->use("fire");
					entity->attrib.isHitting = true;			// đang đánh
					animations->animFinished = false;
					break;
				default:
					break;
				}
				
			}
			else if (sprite->ID == PLAYER2ID && animations->animFinished)
			{
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_UP:
					transform->velocity.y = -3;
					animations->animFinished = false;
					animations->use("jump");
					break;
				case SDLK_RIGHT:
					transform->velocity.x = 0.5;
					sprite->spriteFlip = SDL_FLIP_NONE;
					animations->animFinished = true;		// sẵn sàng nhận phím tiếp theo
					animations->use("run");
					break;
				case SDLK_LEFT:
					transform->velocity.x = -0.5;
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					animations->animFinished = true;		// sẵn sàng nhận phím tiếp theo
					animations->use("run");
					break;
				case SDLK_1:
					transform->velocity.x = 0;
					animations->use("attackcb");
					entity->attrib.isHitting = true;			// đang đánh
					animations->animFinished = false;
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
			//	animations->state("idle");
			//	break;
			//case SDLK_a:
			//	transform->velocity.x = 0;
			//	sprite->spriteFlip = flip;		// nhân vật giữ yên hướng vẽ
			//	animations->state("idle");
			//	break;
			//case SDLK_d:
			//	transform->velocity.x = 0;
			//	sprite->spriteFlip = flip;
			//	animations->state("idle");
			//	break;
			//case SDLK_u:
			//	transform->velocity.x = 0;
			//	animations->state("idle");
			//	break;
			//default:
			//	break;
			//}
		}
	}
};