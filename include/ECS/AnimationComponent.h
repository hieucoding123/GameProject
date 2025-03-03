#pragma once

#include "TransformComponent.h"
#include "SpriteComponent.h"

class AnimationComponent : public Component
{
public:
	const char* state = "idle";			// trạng thái
	bool animFinished = true;

	AnimationComponent() = default;
	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			transform = &entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		if (!entity->hasComponent<SpriteComponent>())
		{
			sprite = &entity->addComponent<SpriteComponent>();
		}
		sprite = &entity->getComponent<SpriteComponent>();

		currentFrame = 0;
		lastUpdate = SDL_GetTicks();
	}
	void update() override
	{
		animInfor = GAMECHARACTERS.at(sprite->ID).at(state);

		if (sprite->isAnimated())
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
					animFinished = true;
					entity->attrib.isHitting = false;
				}
			}
		}
		
		// cập nhật kích thước ảnh gốc
		transform->width = animInfor[4];
		transform->high = animInfor[5];

		// cho dịch khung hình
		sprite->setSrcX(transform->width * currentFrame);
		sprite->setSrcY(animInfor[3]);
	}

	void use(const char* animation)
	{
		state = animation;
		animInfor = GAMECHARACTERS.at(sprite->ID).at(state);
		frames = animInfor[0];
		speed = animInfor[1];
		sprite->setSrcW(animInfor[4]);
		sprite->setSrcH(animInfor[5]);
		entity->attrib.isHitting = (bool)animInfor[6];
		entity->attrib.damage = animInfor[7] / speed;

		lastUpdate = SDL_GetTicks();		// đặt lại tgian
		currentFrame = 0;
	}
private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	int frames = 4;		// số khung hình
	int speed = 150;	// tốc độ

	std::vector<int> animInfor;
	Uint32 lastUpdate;
	int currentFrame;
};