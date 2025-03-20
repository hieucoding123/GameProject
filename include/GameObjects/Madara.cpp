#include "Madara.h"
#include "EffectManager.h"
#include "PlaySection.h"

Madara::Madara()
{
	GameObject::GameObject();
}

// khởi tạo
void Madara::init()
{
	GameObject::init();
	transform->setSpeed(5);
	sprite = std::make_unique<SpriteComponent>(MADARA_IMG_PATH, rect);
	sprite->getSrcRect()->w = 61;
	sprite->getSrcRect()->h = 89;
	animation = std::make_unique<Animation>(attrib.get(), transform->getVelocity(), sprite->getSrcRect(), MADARA);
}
void Madara::update()
{
	GameObject::update();
	// cập nhật vị trí trên màn hình

	if (transform->getYPos() + rect->h >= (GROUND * PlaySection::MAP_SCALE))
	{
		transform->setYpos((GROUND * PlaySection::MAP_SCALE) - rect->h);
	}
	if (transform->getXPos() + rect->w >= (WIDTH * PlaySection::MAP_SCALE))
	{
		transform->setXPos(WIDTH * PlaySection::MAP_SCALE - rect->w);
	}
	if (this->hasCamera())
	{
		rect->x = transform->getXPos() - PlaySection::camera.x;
		rect->y = transform->getYPos() - PlaySection::camera.y;
	}
	else {
		rect->x = transform->getXPos();
		rect->y = transform->getYPos();
	}
	animation->update();

	// cập nhật va chạm với hiệu ứng
	//std::cout << "Madara\n";
	PlaySection::effectManager.checkVar(attrib.get(), rect.get());
	//std::cout << "****\n";
}
void Madara::draw()
{
	GameObject::draw();
}

void Madara::ADWSController()
{
	if (Game::event.type == SDL_KEYDOWN && animation->isFinished())
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_d:
			if (animation->setStateSuccess((int)SDLK_d))
			{
				transform->setVx(1);
				animation->setFinished(true);
				sprite->setFlip(SDL_FLIP_NONE);
			}
			break;
		case SDLK_a:
			if (animation->setStateSuccess((int)SDLK_d))
			{
				transform->setVx(-1);
				animation->setFinished(true);
				sprite->setFlip(SDL_FLIP_HORIZONTAL);
			}
			break;
		case SDLK_w:
			if (animation->setStateSuccess((int)SDLK_w))
			{
				transform->setVy(-3);
				animation->setFinished(false);
			}
			break;
		case SDLK_r:
			if (animation->setStateSuccess((int)SDLK_r))
			{
				transform->setVx(0);
				animation->setFinished(false);
				PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-3),
					0, 0, 2, sprite->getFlip(), rect->x + 586 * sprite->getROL() - 464, rect->y - 170));
			}
			break;
		case SDLK_u:
			animation->setStateSuccess((attrib->onGround) ? (int)SDLK_u : (int)SDLK_e);
			transform->setVx(0);
			animation->setFinished(false);
			break;
		/*case SDLK_c:
			transform->setVx(0);
			animation->setStateSuccess((attrib->onGround) ? (int)SDLK_c : (int)SDLK_q);
			animation->setFinished(false);
			break;*/
		/*case SDLK_f:
			transform->setVx(4 * sprite->getROL());
			animation->setStateSuccess((int)SDLK_f);
			animation->setFinished(false);
			Game::playSound(4);
			break;*/
		/*case SDLK_1:
			transform->setVx(0);
			animation->setStateSuccess((int)SDLK_1);
			animation->setFinished(false);
			PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-6),
				9, 0, 2, sprite->getFlip(), rect->x + rect->w * sprite->getROL(), rect->y - 300));
			break;*/
		case SDLK_2:
			if (animation->setStateSuccess((int)SDLK_2))
			{
				transform->setVx(0);
				animation->setFinished(false);
				PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-5),
					0, 0, 3, SDL_FLIP_NONE, rect->x + rect->w * 1.0 / 2 - 350, rect->y - 600));
				PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-7),
					0, 7, 6, sprite->getFlip(), rect->x + 900 * sprite->getROL(), -800));
			}
			break;
		default:
			break;
		}
	}
}

void Madara::LRUDController()
{
	if (Game::event.type == SDL_KEYDOWN && animation->isFinished())
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			
			if (animation->setStateSuccess((int)SDLK_d))
			{
				transform->setVx(1);
				animation->setFinished(true);
				sprite->setFlip(SDL_FLIP_NONE);
			}
			break;
		case SDLK_LEFT:
			if (animation->setStateSuccess((int)SDLK_d))
			{
				transform->setVx(-1);
				animation->setFinished(true);
				sprite->setFlip(SDL_FLIP_HORIZONTAL);
			}
			break;
		case SDLK_UP:
			if (animation->setStateSuccess((int)SDLK_w))
			{
				transform->setVy(-3);
				animation->setFinished(false);
			}
			break;
		case SDLK_m:
			if (animation->setStateSuccess((int)SDLK_r))
			{
				transform->setVx(0);
				animation->setFinished(false);
				PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-3),
					0, 0, 2, sprite->getFlip(), rect->x + 586 * sprite->getROL() - 464, rect->y - 170));
			}
			break;
		case SDLK_k:
			animation->setStateSuccess((attrib->onGround) ? (int)SDLK_u : (int)SDLK_e);
			transform->setVx(0);
			animation->setFinished(false);
			break;
		/*case SDLK_l:
			transform->setVx(0);
			animation->setStateSuccess((attrib->onGround) ? (int)SDLK_c : (int)SDLK_q);
			animation->setFinished(false);
			break;*/
		/*case SDLK_RCTRL:
			transform->setVx(4 * sprite->getROL());
			animation->setStateSuccess((int)SDLK_f);
			animation->setFinished(false);
			Game::playSound(4);
			break;*/
		/*case SDLK_SLASH:
			transform->setVx(0);
			animation->setStateSuccess((int)SDLK_1);
			animation->setFinished(false);
			PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-6),
				9, 0, 2, sprite->getFlip(), rect->x + rect->w * sprite->getROL(), rect->y - 300));
			break;*/
		case SDLK_PERIOD:
			if (animation->setStateSuccess((int)SDLK_2))
			{
				transform->setVx(0);
				PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-5),
					0, 0, 3, SDL_FLIP_NONE, rect->x + rect->w * 1.0 / 2 - 350, rect->y - 600));
				PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-7),
					0, 7, 6, sprite->getFlip(), rect->x + 900 * sprite->getROL(), -800));
				animation->setFinished(false);
			}
			break;
		default:
			break;
		}
	}
}
