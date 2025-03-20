//#pragma once
//
//#include <iostream>
//#include <vector>
//#include <bitset>
//#include <array>
//#include <memory>
//#include <algorithm>
//#include "Game.h"
//#include "Const.h"
//
//class Manager;
//class Entity;
//class Component;
//
//
//using ComponentID = std::size_t;
//constexpr ComponentID maxComponents = 32;
//using ComponentBitset = std::bitset<maxComponents>;
//using ComponentArray = std::array<Component*, maxComponents>;
//
//using Group = std::size_t;
//constexpr std::size_t maxGroups = 32;
//using GroupBitset = std::bitset<maxGroups>;
//
//
//inline ComponentID getComponentID()
//{
//	static ComponentID lastID = 0;
//	return lastID++;
//}
//
//
//// mỗi T nhận 1 ID riêng
//template<class T> inline ComponentID getComponentID() noexcept
//{
//	static ComponentID typeID = getComponentID();
//	return typeID;
//}
//
//
//class Component
//{
//public:
//	Entity* entity;
//		
//	virtual void init() {}
//	virtual void update() {}
//	virtual void draw() {}
//
//	virtual ~Component() {}
//};
//
//struct Attribute
//{
//	double hp = HP;			// máu
//	int energy = 0;			// năng lượng
//	double damage = 0;		// sát thương
//	int defense = DEFENSE;	// phòng thủ
//	const char* state = "idle";
//	bool onGround = true;	// chạm đất
//	bool isHitting = false;	// đánh / không
//};
//
//class Entity
//{
//private:
//	Manager& manager;
//	ComponentBitset componentBitset;		// true / false
//	ComponentArray componentArray;			// component
//	GroupBitset groupBitset;
//
//	std::vector<std::unique_ptr<Component>> components;
//	SDL_Rect rect;
//	bool active = true;
//public:
//	Attribute attrib;
//
//	Entity(Manager& mManager) : manager(mManager)
//	{ }
//
//	void update()
//	{
//		for (auto& c : components) c->update();
//	}
//	void draw()
//	{
//		for (auto& c : components) c->draw();
//	}
//
//	bool isActive() const { return active; }
//	void destroy() { active = false; }
//	SDL_Rect getRect() const { return rect; }
//
//	SDL_Rect* Rect() { return &rect; }			// cập nhật rect trên màn hình
//
//	// thêm component
//	template<class T, class ... TArgs>
//	T& addComponent(TArgs&& ... mArgs)
//	{
//		T* c(new T(std::forward<TArgs>(mArgs)...));
//		c->entity = this;
//		std::unique_ptr<Component> uPtr{ c };
//		components.emplace_back(std::move(uPtr));
//
//		componentArray[getComponentID<T>()] = c;
//		componentBitset[getComponentID<T>()] = true;
//		c->init();
//
//		return *c;
//	}
//
//	// lấy ra component
//	template<class T> T& getComponent() const
//	{
//		auto ptr(componentArray[getComponentID<T>()]);
//
//		return *static_cast<T*>(ptr);
//	}
//
//	// có T trong Entity không
//	template<class T> bool hasComponent() const
//	{
//		return componentBitset[getComponentID<T>()];
//	}
//
//	void delGroup(Group mGroup)
//	{
//		groupBitset[mGroup] = false;
//	}
//
//	// thêm 
//	void addGroup(Group mGroup);
//
//	bool hasGroup(Group mGroup)
//	{
//		return groupBitset[mGroup];
//	}
//};
//
//class Manager
//{
//private:
//	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
//	std::vector<std::unique_ptr<Entity>> entities;
//public:
//	void update()
//	{
//		for (auto& e : entities) e->update();
//
//		//// Kiểm tra va chạm
//		//int i = 0;
//		//for (auto& effect : Game::effects)
//		//{
//		//	for (int j = 0; j < entities.size(); j++)
//		//	{
//		//		if (j != i && Game::AABB(effect->destRect, entities[j]->getRect()) &&
//		//			effect->getDamage() > 0)		// áp dụng hiệu ứng lên đối tượng khác
//		//		{
//		//			entities[j]->attrib.hp -= effect->getDamage();
//		//			effect->setDamge();
//		//		}
//		//	}
//		//	i++;
//		//}
//	}
//	void draw()
//	{
//		for (auto& e : entities) e->draw();
//	}
//
//	// thêm entity
//	Entity& addEntity()
//	{
//		Entity* e = new Entity(*this);
//		std::unique_ptr<Entity> uPtr{ e };
//		entities.emplace_back(std::move(uPtr));
//
//		return *e;
//	}
//	// xóa entity không hoạt động
//	void refresh()
//	{
//	
//		for (auto i(0u); i < maxGroups; i++)
//		{
//			auto& v(groupedEntities[i]);
//			v.erase(std::remove_if(std::begin(v), std::end(v),
//				[i](Entity* mEntity) {
//					return !mEntity->isActive() || !mEntity->hasGroup(i);
//				}), std::end(v));
//		}
//
//		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
//			[](const std::unique_ptr<Entity>& mEntity) {
//				return !mEntity->isActive();
//			}), std::end(entities));
//	}
//	
//	// thêm entity vào group
//	void addToGroup(Entity* mEntity, Group mGroup)
//	{
//		groupedEntities[mGroup].emplace_back(mEntity);
//	}
//
//	std::vector<Entity*>& getGroup(Group mGroup)
//	{
//		return groupedEntities[mGroup];
//	}
//};