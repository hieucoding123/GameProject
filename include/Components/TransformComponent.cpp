#include "TransformComponent.h"
#include "Const.h"

TransformComponent::TransformComponent()
{
	position = std::make_unique<Vector2D>();
	velocity = std::make_unique<Vector2D>();
}
TransformComponent::TransformComponent(int x, int y)
{
	position = std::make_unique<Vector2D>();
	velocity = std::make_unique<Vector2D>();
	position->x = x;
	position->y = y;

	velocity->x = velocity->y = 0;
}

int TransformComponent::getXPos() const { return position->x; }

int TransformComponent::getYPos() const { return position->y; }

void TransformComponent::setXPos(int pos)
{
	position->x = pos;
}
void TransformComponent::setYpos(int pos)
{
	position->y = pos;
}


void TransformComponent::setVx(int n)
{
	velocity->x = n;
}

void TransformComponent::setVy(int n)
{
	velocity->y = n;
}

void TransformComponent::setSpeed(int s)
{
	speed = s;
}

Vector2D* TransformComponent::getVelocity()
{
	return velocity.get();
}
void TransformComponent::init()
{
	position->x = position->y = 0;
	velocity->x = velocity->y = 0;
}
void TransformComponent::update()
{
	position->x += velocity->x * speed;
	position->y += velocity->y * speed;

	position->y += GRAVITY;

	if (position->x <= 0) position->x = 0;
}


TransformComponent::~TransformComponent()
{

}