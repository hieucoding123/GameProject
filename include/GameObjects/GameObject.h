#pragma once

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
	* @return chỉ số HP
	*/
	int getHP() const;
	/*
	* Lấy ra chỉ số năng lượng
	* @return chỉ số năng lượng
	*/
	int getEnergy() const;
	
	/*
	* Lấy ra vị trí x
	* @return vị trí thực trên trục x
	*/
	int getXpos() const;

	/*
	* Lấy ra vị trí y
	* @return vị trí thực trên trục y
	*/
	int getYpos() const;

	/*
	* Lấy ra chiều rộng 
	* @return chiều rộng đối tượng
	*/
	int getWidth() const { return rect->w; }

	/*
	* Lấy ra chiều cao
	* @return chiều cao đối tượng
	*/
	int getHigh() const { return rect->h; }

	~GameObject();
protected:
	std::unique_ptr<TransformComponent> transform;
	std::unique_ptr<SpriteComponent> sprite;
	std::unique_ptr<SDL_Rect> rect;
	std::unique_ptr<Attribute> attrib;
private:
	bool isActive;
};