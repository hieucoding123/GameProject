#include "Bot.h"
#include "EffectManager.h"
#include <cstdlib>

Bot::Bot()
{
	GameObject::GameObject();
}

void Bot::init()
{
	GameObject::init();
	attrib->ID = -1;			// Tất cả bot đều chung ID
	attrib->state = 0;			// Mặc định ban đầu đứng yên
	attrib->hp = BOT_HP;
	transform->setSpeed(3);
	sprite = std::make_unique<SpriteComponent>(BOT_IMG_PATH, rect);
	sprite->getSrcRect()->w = 61;
	sprite->getSrcRect()->h = 89;

	frames = BOT.at(0)[0];
	speed = BOT.at(0)[1];
	sprite->getSrcRect()->x = BOT.at(0)[2];
	sprite->getSrcRect()->y = BOT.at(0)[3];
	sprite->getSrcRect()->w = BOT.at(0)[4];
	sprite->getSrcRect()->h = BOT.at(0)[5];

	currentFrame = 0;
	lastUpdate = SDL_GetTicks();
	animFinished = false;
}

void Bot::setAnimation(int state)
{
	attrib->state = state;
	frames = BOT.at(state)[0];
	speed = BOT.at(state)[1];
	sprite->getSrcRect()->x = BOT.at(state)[2];
	sprite->getSrcRect()->y = BOT.at(state)[3];
	sprite->getSrcRect()->w = BOT.at(state)[4];
	sprite->getSrcRect()->h = BOT.at(state)[5];
	// Cài đặt sát thương cận chiến
	attrib->damage = BOT.at(state)[7];

	currentFrame = 0;
	lastUpdate = SDL_GetTicks();
	animFinished = false;
}

void Bot::update()
{
	// Cập nhật vị trí
	transform->update();
	if (transform->getYPos() + rect->h >= (GROUND * PlaySection::MAP_SCALE))
	{
		transform->setYpos((GROUND * PlaySection::MAP_SCALE) - rect->h);
	}
	if (transform->getXPos() + rect->w >= (WIDTH * PlaySection::MAP_SCALE))
	{
		transform->setXPos(WIDTH * PlaySection::MAP_SCALE - rect->w);
	}
	rect->x = transform->getXPos() - PlaySection::camera.x;
	rect->y = transform->getYPos() - PlaySection::camera.y;

	sprite->update();

	// Cập nhật hoạt hình

	if ((attrib->hp < 0) || animFinished || attrib->isHitting)
	{
		if ((attrib->hp < 0) && animFinished)
		{
			setAnimation(7);
			transform->setVx(0);
			transform->setVy(0);
			animFinished = false;
		}
		else if (attrib->isHitting)
		{
			setAnimation(5);
			transform->setVx(0);
			transform->setVy(0);
			attrib->isHitting = false;
		}
		else if (animFinished) {
			// Lật ảnh ngẫu nhiên
			SDL_RendererFlip randomFlip = SDL_RendererFlip(rand() % 2);
			sprite->setFlip(randomFlip);

			// Trạng thái ngẫu nhiên
			int randomState = rand() % (BOT.size() - 3);
			setAnimation(randomState);
		}

		switch (attrib->state)
		{
		case 0:
			transform->setVx(0);
			transform->setVy(0);
			break;
		case 1:
			transform->setVx(sprite->getROL() * 1);
			transform->setVy(0);
			break;
		case 2:
			transform->setVx(sprite->getROL() * 2);
			transform->setVy(0);
			break;
		case 3:
			transform->setVx(0);
			transform->setVy(0);
		case 4:
			transform->setVx(0);
			transform->setVy(0);
			PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, BOT.at(6),
				9, 0, 1, sprite->getFlip(), transform->getXPos(), transform->getYPos() + 50));
		default:
			break;
		}

	}
	Uint32 now = SDL_GetTicks();
	if (now - lastUpdate > speed)
	{
		currentFrame++;
		lastUpdate = now;
		sprite->getSrcRect()->x += sprite->getSrcRect()->w;
		
		if (currentFrame >= frames)
		{
			if (attrib->state == 7)
			{
				sprite->getSrcRect()->x = BOT.at(7)[2] + (frames - 1) * sprite->getSrcRect()->w;
				attrib->isDie = true;
			}
			else {
				animFinished = true;
			}
		}
	}
	PlaySection::effectManager.checkVar(attrib.get(), rect.get());
}

void Bot::draw()
{
	sprite->draw();

	// Vẽ thanh máu cho bot
	TextureManager::DrawHP(rect->x, rect->y, (attrib->hp * BOT_HP_W) / BOT_HP,
		BOT_HP_H, BOT_HP_W, HPBG_COLOR, HP_COLOR);
}