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

	animation->update();

	// cập nhật va chạm với hiệu ứng
	PlaySection::effectManager.checkVar(attrib.get(), rect.get());
}
void Madara::draw()
{
	GameObject::draw();
}

void Madara::ADWSController()
{
	if (Game::event.type == SDL_KEYDOWN && animation->isFinished())
	{
		int x = transform->getXPos();
		int y = transform->getYPos();
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
				transform->setVy(-4);
				animation->setFinished(false);
				Game::playSound(5);
			}
			break;
		case SDLK_r:
			if (attrib->onGround)
			{
				if (animation->setStateSuccess((int)SDLK_r))
				{
					transform->setVx(0);
					animation->setFinished(false);
					PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-3),
						0, 0, 2, sprite->getFlip(), x + 586 * sprite->getROL() - 464, y - 170));
					Game::playSound(6);
				}
			}
			else {
				if (animation->setStateSuccess((int)SDLK_t))
				{
					transform->setVx(0);
					transform->setVy(-1);
					animation->setFinished(false);
					PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-8),
						9, 5, 1, sprite->getFlip(), x + 100 * sprite->getROL(), y));
					PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-8),
						9, 5, 1, sprite->getFlip(), x + 10 * sprite->getROL(), y + 30));
					PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-8),
						9, 5, 1, sprite->getFlip(), x + 200 * sprite->getROL(), y + 10));
					Game::playSound(6);
				}
			}
			break;
		case SDLK_u:
			animation->setStateSuccess((attrib->onGround) ? (int)SDLK_u : (int)SDLK_e);
			transform->setVx(0);
			animation->setFinished(false);
			break;
		case SDLK_c:
			transform->setVx(0);
			animation->setStateSuccess((int)SDLK_c);
			animation->setFinished(false);
			break;
		case SDLK_f:
			transform->setVx(4 * sprite->getROL());
			animation->setStateSuccess((int)SDLK_f);
			animation->setFinished(false);
			Game::playSound(4);
			break;
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
					0, 0, 3, SDL_FLIP_NONE, x + rect->w * 1.0 / 2 - 350, y - 600));
				PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-7),
					0, 7, 6, SDL_FLIP_NONE, x + 1151 * sprite->getROL() - 501, -800 + PlaySection::camera.y));
				Game::playSound(9);
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
		int x = transform->getXPos();
		int y = transform->getYPos();
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
				transform->setVy(-4);
				animation->setFinished(false);
				Game::playSound(5);
			}
			break;
		case SDLK_m:
			if (attrib->onGround)
			{
				if (animation->setStateSuccess((int)SDLK_r))
				{
					transform->setVx(0);
					animation->setFinished(false);
					PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-3),
						0, 0, 2, sprite->getFlip(), x + 586 * sprite->getROL() - 464, y - 170));
					Game::playSound(6);
				}
			}
			else {
				if (animation->setStateSuccess((int)SDLK_t))
				{
					transform->setVx(0);
					transform->setVy(-1);
					animation->setFinished(false);
					PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-8),
						9, 5, 2, sprite->getFlip(), x + 100 * sprite->getROL(), y));
					PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-8),
						9, 5, 2, sprite->getFlip(), x + 10 * sprite->getROL(), y + 30));
					PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-8),
						9, 5, 2, sprite->getFlip(), x + 200 * sprite->getROL(), y + 10));
				}
			}
			break;
		case SDLK_k:
			animation->setStateSuccess((attrib->onGround) ? (int)SDLK_u : (int)SDLK_e);
			transform->setVx(0);
			animation->setFinished(false);
			break;
		case SDLK_l:
			transform->setVx(0);
			animation->setStateSuccess((int)SDLK_c);
			animation->setFinished(false);
			break;
		case SDLK_RCTRL:
			transform->setVx(4 * sprite->getROL());
			animation->setStateSuccess((int)SDLK_f);
			animation->setFinished(false);
			Game::playSound(4);
			break;
		/*case SDLK_KP_1:
			transform->setVx(0);
			animation->setStateSuccess((int)SDLK_1);
			animation->setFinished(false);
			PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-6),
				9, 0, 2, sprite->getFlip(), rect->x + rect->w * sprite->getROL(), rect->y - 300));
			break;*/
		case SDLK_KP_2:
			if (animation->setStateSuccess((int)SDLK_2))
			{
				transform->setVx(0);
				PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-5),
					0, 0, 3, SDL_FLIP_NONE, x + rect->w * 1.0 / 2 - 350, y - 600));
				PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-7),
					0, 7, 6, SDL_FLIP_NONE, x + 1151 * sprite->getROL() - 501, -800 + PlaySection::camera.y));
				animation->setFinished(false);
				Game::playSound(9);
			}
			break;
		default:
			break;
		}
	}
}
