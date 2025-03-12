#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include "Effect.h"
#include "Components/Attribute.h"

class EffectManager
{
public:
	EffectManager() = default;
	void addEffect(std::unique_ptr<Effect> e);
	void update();
	void draw();
	void checkVar(Attribute* attrib, SDL_Rect* rect);
private:
	std::vector<std::unique_ptr<Effect>> effects;
};