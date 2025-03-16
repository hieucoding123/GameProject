#pragma once

#include "GameObject.h"
#include "Components/Animation.h"

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
private:
	std::unique_ptr<Animation> animation;
};