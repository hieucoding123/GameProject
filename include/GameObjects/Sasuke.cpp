#include "Sasuke.h"
#include "EffectManager.h"
#include "PlaySection.h"

Sasuke::Sasuke()
{
	GameObject::GameObject();
}

// khởi tạo
void Sasuke::init()
{
	GameObject::init();
	transform->setSpeed(5);
	sprite = std::make_unique<SpriteComponent>(SASUKE_IMG_PATH, rect);
	sprite->getSrcRect()->w = 48;
	sprite->getSrcRect()->h = 75;
	animation = std::make_unique<Animation>(attrib.get(), transform->getVelocity(), sprite->getSrcRect(), SASUKE);
}
void Sasuke::update()
{
	GameObject::update();
	// Không cho đối tượng ra thoát khỏi map

	if (transform->getYPos() + rect->h >= (GROUND * PlaySection::MAP_SCALE))
	{
		transform->setYpos((GROUND * PlaySection::MAP_SCALE) - rect->h);
	}
	if (transform->getXPos() + rect->w >= (WIDTH * PlaySection::MAP_SCALE))
	{
		transform->setXPos(WIDTH * PlaySection::MAP_SCALE - rect->w);
	}
	
	animation->update();

	PlaySection::effectManager.checkVar(attrib.get(), rect.get());
}
void Sasuke::draw()
{
	GameObject::draw();
}

void Sasuke::ADWSController()
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
				transform->setVy(-3);
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
						9, 0, 2, sprite->getFlip(), x + 70 * sprite->getROL(), y));
					Game::playSound(6);
				}
			}
			else {		// chiêu tương tự nhưng ở trên không
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
			if (animation->setStateSuccess((attrib->onGround) ? (int)SDLK_c : (int)SDLK_q))
			{
				transform->setVx(0);
				animation->setFinished(false);
			}
			break;
		case SDLK_f:
			if (animation->setStateSuccess((int)SDLK_f))
			{
				transform->setVx(4 * sprite->getROL());
				animation->setFinished(false);
				Game::playSound(4);
			}
			break;
		case SDLK_1:
			if (animation->setStateSuccess((int)SDLK_1))
			{
				transform->setVx(0);
				animation->setFinished(false);
				PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-6),
					9, 0, 3, sprite->getFlip(), x + rect->w * sprite->getROL(), y - 600));
				Game::playSound(9);
			}
			break;
		case SDLK_2:
			if (animation->setStateSuccess((int)SDLK_2))
			{
				transform->setVx(0);
				PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-7),
					0, 0, 2, sprite->getFlip(), x, y - 240));
				PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-5),
					12, 0, 3, sprite->getFlip(), x, y - 120));
				animation->setFinished(false);
				Game::playSound(9);
			}
			break;
		default:
			break;
		}
	}
}

void Sasuke::LRUDController()
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
				transform->setVy(-3);
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
						9, 0, 2, sprite->getFlip(), x + 70 * sprite->getROL(), y));
					Game::playSound(6);
				}
			}
			else {		// chiêu tương tự nhưng ở trên không
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
					Game::playSound(6);
				}
			}
			break;
		case SDLK_k:
			animation->setStateSuccess((attrib->onGround) ? (int)SDLK_u : (int)SDLK_e);
			transform->setVx(0);
			animation->setFinished(false);
			break;
		case SDLK_l:
			if (animation->setStateSuccess((attrib->onGround) ? (int)SDLK_c : (int)SDLK_q))
			{
				transform->setVx(0);
				animation->setFinished(false);
			}
			break;
		case SDLK_RCTRL:
			if (animation->setStateSuccess((int)SDLK_f))
			{
				transform->setVx(4 * sprite->getROL());
				animation->setFinished(false);
				Game::playSound(4);
			}
			break;
		case SDLK_KP_1:
			if (animation->setStateSuccess((int)SDLK_1))
			{
				transform->setVx(0);
				animation->setFinished(false);
				PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-6),
					9, 0, 3, sprite->getFlip(), x + rect->w * sprite->getROL(), y - 600));
				Game::playSound(9);
			}
			break;
		case SDLK_KP_2:
			if (animation->setStateSuccess((int)SDLK_1))
			{
				transform->setVx(0);
				PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-7),
					0, 0, 2, sprite->getFlip(), x, y - 240));
				PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-5),
					12, 0, 3, sprite->getFlip(), x, y - 120));
				Game::playSound(9);
			}
			animation->setFinished(false);
			break;
		default:
			break;
		}
	}
}
