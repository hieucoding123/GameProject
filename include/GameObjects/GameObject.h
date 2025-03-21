﻿#pragma once

#include <memory>
#include "SDL.h"
#include "Components/Attribute.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "EffectManager.h"

inline int genID()
{
	static int ID = 0;
	return ID++;
}

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
	void setPosition(int xpos, int ypos);
	/*
	* Lấy ra chỉ số HP
	*/
	int getHP() const;
	/*
	* Lấy ra chỉ số năng lượng
	*/
	int getEnergy() const;
	~GameObject();
protected:
	std::unique_ptr<TransformComponent> transform;
	std::unique_ptr<SpriteComponent> sprite;
	std::unique_ptr<SDL_Rect> rect;
	std::unique_ptr<Attribute> attrib;
private:
	bool isActive;
};