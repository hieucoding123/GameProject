#include "Sasuke.h"
#include "EffectManager.h"

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
	// cập nhật vị trí trên màn hình

	if (transform->getYPos() + rect->h >= (GROUND * Game::MAP_SCALE))
	{
		transform->setYpos((GROUND * Game::MAP_SCALE) - rect->h);
	}
	if (transform->getXPos() + rect->w >= (WIDTH * Game::MAP_SCALE))
	{
		transform->setXPos(WIDTH * Game::MAP_SCALE - rect->w);
	}
	if (this->hasCamera())
	{
		rect->x = transform->getXPos() - Game::camera.x;
		rect->y = transform->getYPos() - Game::camera.y;
	}
	else {
		rect->x = transform->getXPos();
		rect->y = transform->getYPos();
	}
	animation->update();

	// cập nhật va chạm với hiệu ứng
	//std::cout << "Sasuke\n";
	Game::effectManager.checkVar(attrib.get(), rect.get());
	//std::cout << "****\n";
}
void Sasuke::draw()
{
	GameObject::draw();
}

void Sasuke::ADWSController()
{
	if (Game::event.type == SDL_KEYDOWN && animation->isFinished())
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_d:
			transform->setVx(1);
			animation->setState((int)SDLK_d);
			animation->setFinished(true);
			sprite->setFlip(SDL_FLIP_NONE);
			break;
		case SDLK_a:
			transform->setVx(-1);
			animation->setState((int)SDLK_d);
			animation->setFinished(true);
			sprite->setFlip(SDL_FLIP_HORIZONTAL);
			break;
		case SDLK_w:
			transform->setVy(-3);
			animation->setState((int)SDLK_w);
			animation->setFinished(false);
			break;
		case SDLK_r:
			transform->setVx(0);
			animation->setState((int)SDLK_r);
			animation->setFinished(false);
			Game::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-3), 
				9, 0, 2, sprite->getFlip(), rect->x + 70 * sprite->getROL(), rect->y));
			break;
		case SDLK_u:
			transform->setVx(0);
			animation->setState((int)SDLK_u);
			animation->setFinished(false);
			break;
		case SDLK_c:
			transform->setVx(0);
			animation->setState((attrib->onGround) ? (int)SDLK_c : (int)SDLK_q);
			animation->setFinished(false);
			break;
		case SDLK_f:
			transform->setVx(4 * sprite->getROL());
			animation->setState((int)SDLK_f);
			animation->setFinished(false);
			Game::playSound(4);
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
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			transform->setVx(1);
			animation->setState((int)SDLK_d);
			animation->setFinished(true);
			sprite->setFlip(SDL_FLIP_NONE);
			break;
		case SDLK_LEFT:
			transform->setVx(-1);
			animation->setState((int)SDLK_d);
			animation->setFinished(true);
			sprite->setFlip(SDL_FLIP_HORIZONTAL);
			break;
		case SDLK_UP:
			transform->setVy(-3);
			animation->setState((int)SDLK_w);
			animation->setFinished(false);
			break;
		case SDLK_m:
			transform->setVx(0);
			animation->setState((int)SDLK_r);
			animation->setFinished(false);
			Game::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-3),
				9, 0, 2, sprite->getFlip(), rect->x + 70 * sprite->getROL(), rect->y));
			break;
		case SDLK_k:
			transform->setVx(0);
			animation->setState((int)SDLK_u);
			animation->setFinished(false);
			break;
		case SDLK_l:
			transform->setVx(0);
			animation->setState((attrib->onGround) ? (int)SDLK_c : (int)SDLK_q);
			animation->setFinished(false);
			break;
		case SDLK_RCTRL:
			transform->setVx(4 * sprite->getROL());
			animation->setState((int)SDLK_f);
			animation->setFinished(false);
			Game::playSound(4);
			break;
		default:
			break;
		}
	}
}

void Sasuke::setPosition(int xpos, int ypos)
{
	transform->setXPos(xpos);
	transform->setYpos(ypos);
}

int	Sasuke::getHP() const
{
	return attrib->hp;
}
int	Sasuke::getEnergy() const
{
	return attrib->energy;
}
