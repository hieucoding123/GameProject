﻿#pragma once

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
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->use("run");
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				sprite->use("run");
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->use("idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->spriteFlip = SDL_FLIP_NONE;
				sprite->use("idle");
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->use("idle");
				break;
			default:
				break;
			}
		}
	}
};