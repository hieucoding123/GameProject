#include "GameObject.h"

GameObject::GameObject()
{
	rect = std::make_unique<SDL_Rect>();
	transform = std::make_unique<TransformComponent>();
	sprite = std::make_unique<SpriteComponent>();
	attrib = std::make_unique<Attribute>();
	attrib->ID = genID();					// gắn mỗi đối tượng 1 id
	isActive = true;
}

void GameObject::setCamera()
{
	attrib->hasCamera = true;
}

bool GameObject::hasCamera() const
{
	return attrib->hasCamera;
}

void GameObject::init()
{
	transform->init();
}
void GameObject::update()
{
	transform->update();

	// Nếu gắn camera thì không cho thoát ra khỏi vùng của camera
	if (this->hasCamera())
	{ 
		int n;

		// Đi quá bên trái
		n = this->transform->getXPos() - PlaySection::camera.x;
		if (n <= 0)
		{
			PlaySection::setCameraX(n);
			this->transform->setXPos(PlaySection::camera.x);
		}

		// Đi quá bên trên
		if (this->transform->getYPos() - PlaySection::camera.y <= 0)
			this->transform->setYpos(PlaySection::camera.y);

		// Đi quá bên phải
		n = this->transform->getXPos() + rect->w - (PlaySection::camera.x + PlaySection::camera.w);
		if (n >= 0)
		{
			PlaySection::setCameraX(n);
			this->transform->setXPos(PlaySection::camera.x + PlaySection::camera.w - rect->w);
		}

		// Đi quá bên dưới
		if (this->transform->getYPos() + rect->h - (PlaySection::camera.y + PlaySection::camera.h) >= 0)
			this->transform->setYpos(PlaySection::camera.y + PlaySection::camera.h - rect->h);

		// Tổng kết lại
		rect->x = transform->getXPos() - PlaySection::camera.x;
		rect->y = transform->getYPos() - PlaySection::camera.y;
	}
	else {
		rect->x = transform->getXPos();
		rect->y = transform->getYPos();
	}

	sprite->update();
	// Kiểm tra chạm với mặt đất
	attrib->onGround = (transform->getYPos() + rect->h >= GROUND * PlaySection::MAP_SCALE);

	// Kiểm tra va chạm với đối tượng khác
	for (auto& object : PlaySection::gameObjects)
	{
		if (object->attrib->ID != attrib->ID && PlaySection::AABB(*rect, *object->rect.get()))
		{
			if (object->attrib->damage > 0) 
			{
				attrib->hp -= object->attrib->damage;
				attrib->isHitting = true;
				object->attrib->damage = 0;
				object->attrib->energy += 32;
				Game::playSound(0);
			}
		}
	}
}
void GameObject::draw()
{
	sprite->draw();
	if (attrib->state == -4) 
		TextureManager::DrawCollisionImage(rect.get());
}

void GameObject::ADWSController()
{
	if (Game::event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_d:
			transform->setVx(1);
			break;
		case SDLK_a:
			transform->setVx(-1);
			break;
		case SDLK_w:
			transform->setVy(-1);
			break;
		default:
			break;
		}
	}
	if (Game::event.type == SDL_KEYUP)
	{
		
	}
}

void GameObject::LRUDController()
{
	if (Game::event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_d:
			transform->setVx(1);
			break;
		case SDLK_a:
			transform->setVx(-1);
			break;
		case SDLK_w:
			transform->setVy(-1);
			break;
		default:
			break;
		}
	}
	if (Game::event.type == SDL_KEYUP)
	{

	}
}

void GameObject::setPosition(int xpos, int ypos)
{
	transform->setXPos(xpos);
	transform->setYpos(ypos);	
}

int GameObject::getHP() const
{
	return attrib->hp;
}

int GameObject::getEnergy() const
{
	return attrib->energy;
}

int GameObject::getXpos() const
{
	return transform->getXPos();
}

int GameObject::getYpos() const
{
	return transform->getYPos();
}

GameObject::~GameObject()
{

}