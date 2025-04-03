#pragma once

#include "GameObject.h"
#include "Components/Animation.h"

// Quái vật mạnh nhất
class Boss : public GameObject
{
public:
	Boss();
	void init() override;
	void update() override;
	void draw() override;
private:
	/*
	* Chuyển trạng thái để chuyển hành động
	* @param state trạng thái chuyển đến
	*/
	void setAnimation(int state);
	int frames;		// số khung hình
	int speed;	// độ nhanh của hành động

	Uint32 lastUpdate;
	int currentFrame;

	bool animFinished;
};