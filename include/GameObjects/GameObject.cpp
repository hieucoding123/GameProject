#include "GameObject.h"

GameObject::GameObject()
{
	rect = std::make_unique<SDL_Rect>();
	transform = std::make_unique<TransformComponent>();
	sprite = std::make_unique<SpriteComponent>();
	attrib = std::make_unique<Attribute>();
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
	sprite->update();
}
void GameObject::draw()
{
	sprite->draw();
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

GameObject::~GameObject()
{

}

