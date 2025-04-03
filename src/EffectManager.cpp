#include "EffectManager.h"
#include "PlaySection.h"

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
		if (attrib->ID != e->getID() &&  PlaySection::AABB(*rect, e->getRect()))
		{
			int damage = e->getDamage();
			if (damage > 0 && PlaySection::AABB(*rect, e->getRect()))
			{
				// nếu đối tượng đang thủ thì giảm sát thương
				if (attrib->state == (int)SDLK_c || attrib->state == (int)SDLK_q)
					damage = (damage <= 30) ? 0 : (damage * 2.0 / 3);
				attrib->hp -= damage;
				attrib->isHitting = (damage > 0);		// bị đánh

				if (attrib->isHitting)
					Game::playSound(0);
				e->disableDamage();
			}
		}
	}
}
