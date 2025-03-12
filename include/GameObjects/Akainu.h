#pragma once

#include "GameObject.h"
#include "ECS/Animation.h"

class Akainu : public GameObject
{
public:
	Akainu();
	// khởi tạo
	void init() override;
	void update() override;
	void draw() override;
	void ADWSController() override;
	void LRUDController() override;
	void setPosition(int xpos, int ypos);
	int getHP() const;
	int getEnergy() const;
private:
	std::unique_ptr<Animation> animation;
};