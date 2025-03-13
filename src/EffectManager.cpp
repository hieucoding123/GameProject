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

void EffectManager::checkVar(Attribute* attrib,SDL_Rect* rect)
{
	for (auto& e : effects)
	{
		// không tính chạm đối tượng tạo ra hiệu ứng
		if (attrib->ID != e->getID() &&  Game::AABB(*rect, e->getRect()))
		{
			int damage = e->getDamage();
			if (damage > 0 && Game::AABB(*rect, e->getRect()))
			{
				attrib->hp -= e->getDamage();
				attrib->isHitting = true;		// bị đánh
				e->setDamage();
			}
		}
	}
}
