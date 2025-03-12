#pragma once

#include <memory>
#include "SDL.h"
#include "Components/Attribute.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "EffectManager.h"



class GameObject
{
public:
	GameObject();
	void setCamera();					// gắn theo camera
	bool hasCamera() const;				// theo camera
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual void ADWSController();		// điều khiển
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