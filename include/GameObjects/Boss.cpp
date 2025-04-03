#include "Boss.h"
#include "EffectManager.h"
#include <cstdlib>

Boss::Boss()
{
	GameObject::GameObject();
}

void Boss::init()
{
	GameObject::init();
	attrib->ID = -1;			// Tất cả bot đều chung ID
	attrib->state = 0;			// Mặc định ban đầu đứng yên
	attrib->hp = BOSS_HP;
	transform->setSpeed(1);
	sprite = std::make_unique<SpriteComponent>(BOSS_IMG_PATH, rect);
	sprite->getSrcRect()->w = 161;
	sprite->getSrcRect()->h = 271;

	frames = BOSS.at(0)[0];
	speed = BOSS.at(0)[1];
	sprite->getSrcRect()->x = BOSS.at(0)[2];
	sprite->getSrcRect()->y = BOSS.at(0)[3];
	sprite->getSrcRect()->w = BOSS.at(0)[4];
	sprite->getSrcRect()->h = BOSS.at(0)[5];

	currentFrame = 0;
	lastUpdate = SDL_GetTicks();
	animFinished = false;
}

void Boss::setAnimation(int state)
{
	attrib->state = state;
	frames = BOSS.at(state)[0];
	speed = BOSS.at(state)[1];
	sprite->getSrcRect()->x = BOSS.at(state)[2];
	sprite->getSrcRect()->y = BOSS.at(state)[3];
	sprite->getSrcRect()->w = BOSS.at(state)[4];
	sprite->getSrcRect()->h = BOSS.at(state)[5];
	// Cài đặt sát thương cận chiến
	attrib->damage = BOSS.at(state)[7];

	currentFrame = 0;
	lastUpdate = SDL_GetTicks();
	animFinished = false;
}

void Boss::update()
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

	if (animFinished || attrib->isHitting)
	{
		if (attrib->isHitting)
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
			int randomState = rand() % (BOSS.size() - 2);
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
			transform->setVx(0);
			transform->setVy(0);
			break;
		case 3:
			transform->setVx(0);
			transform->setVy(0);
		case 4:
			transform->setVx(0);
			transform->setVy(0);
			PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, BOSS.at(6),
				0, 0, 2, SDL_FLIP_NONE, transform->getXPos() + sprite->getROL() * (rand() % PlaySection::camera.w), transform->getYPos() + 50));
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
			animFinished = true;
		}
	}
	PlaySection::effectManager.checkVar(attrib.get(), rect.get());

	attrib->isDie = attrib->hp < 0;
}

void Boss::draw()
{
	sprite->draw();

	// Vẽ thanh máu cho bot
	TextureManager::DrawHP(rect->x, rect->y, (attrib->hp * BOSS_HP_W) / BOSS_HP,
		BOSS_HP_H, BOSS_HP_W, HPBG_COLOR, HP_COLOR);
}