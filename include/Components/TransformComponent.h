#pragma once
#include "Vector2D.h"

class TransformComponent
{
public:
	TransformComponent();
	TransformComponent(int x, int y);
	void init();
	void update();
	// vị trí x
	int getXPos() const;

	// vị trí y
	int getYPos() const;

	void setXPos(int pos);
	void setYpos(int pos);
	// điều chỉnh tốc độ x
	void setVx(int n);

	// điều chỉnh tốc độ y
	void setVy(int n);

	void setSpeed(int s);

	Vector2D* getVelocity();

	~TransformComponent();
private:
	std::unique_ptr<Vector2D> position;
	std::unique_ptr<Vector2D> velocity;

	int speed = 5;
};