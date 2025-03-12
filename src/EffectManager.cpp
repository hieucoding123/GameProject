#include "EffectManager.h"

void EffectManager::addEffect(std::unique_ptr<Effect> e)
{
	effects.push_back(std::move(e));
}

void EffectManager::update()
{
	for (auto& e : effects)
	{
		e->update();
	}

	effects.erase(std::remove_if(std::begin(effects), std::end(effects),
		[](const std::unique_ptr<Effect>& e) {
			return !e->isActive();
		}), std::end(effects));
}

void EffectManager::draw()
{
	for (auto& e : effects)
	{
		e->draw();
	}
}