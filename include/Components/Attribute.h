#pragma once
#include "Const.h"

// các thuộc tính cơ bản
struct Attribute
{
	double hp = HP;			// máu
	int energy = 0;			// năng lượng
	double damage = 0;		// sát thương
	int defense = DEFENSE;	// phòng thủ
	int state = -1;
	bool onGround = true;	// chạm đất
	bool isHitting = false;	// đánh / không	
	bool hasCamera = false;
	int ID;
};