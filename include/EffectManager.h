#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "Effect.h"

class EffectManager
{
public:
	EffectManager() = default;
	void addEffect(std::unique_ptr<Effect> e);
	void update();
	void draw();
private:
	std::vector<std::unique_ptr<Effect>> effects;
};