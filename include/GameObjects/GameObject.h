#pragma once

#include <memory>
#include "SDL.h"
#include "Attribute.h"
#include "ECS/TransformComponent.h"
#include "ECS/SpriteComponent.h"
#include "EffectManager.h"



class GameObject
{
public:
	GameObject();
	void setCamera();
	bool hasCamera() const;
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual void ADWSController();
	virtual void LRUDController();
	~GameObject();
protected:
	std::unique_ptr<TransformComponent> transform;
	std::unique_ptr<SpriteComponent> sprite;
	std::unique_ptr<SDL_Rect> rect;
	std::unique_ptr<Attribute> attrib;
private:
	bool isActive;
};