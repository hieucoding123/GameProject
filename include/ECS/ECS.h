#pragma once

#include <iostream>
#include <vector>
#include <bitset>
#include <array>
#include <memory>
#include <algorithm>

class Manager;
class Entity;
class Component;


using ComponentID = std::size_t;
constexpr ComponentID maxComponents = 32;
using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;


inline ComponentID getComponentID()
{
	static ComponentID lastID = 0;
	return lastID++;
}


// mỗi T nhận 1 ID riêng
template<class T> Component getComponentID() noexcept
{
	static ComponentID typeID = getComponentID();
	return typeID;
}


class Component
{
public:
	
	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}
	virtual ~Component() {}
};

class Entity
{
private:
	ComponentBitset componentBitset;
	ComponentArray componentArray;
	std::vector<std::unique_ptr<Component>> components;
	bool active = true;

public:
	void update()
	{
		for (auto& c : components) c->update();
	}
	void draw()
	{
		for (auto& c : components) c->draw();
	}

	bool isActive() const { return active; }
	void destroy() { active = false; }

	// thêm component
	template<class T, class ... TArgs>
	T& addComponent(TArgs&& ... mArgs)
	{
		T* c(new T(std::forward(TArgs) < mArgs > ...));
		c->entity = this;
		std::unique_ptr<T> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentID<T>()] = c;
		componentBitset[getComponentID<T>()] = true;
		c->init();

		return *c;
	}

	// lấy ra component
	template<class T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentID<T>()]);

		return *static_cast<T*>(ptr);
	}

	// có T trong Entity không
	template<class T> bool hasComponent() const
	{
		return ComponentBitset[getComponentID<T>()];
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	
public:
	void update()
	{
		for (auto& e : entities) e->update();
	}
	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	// thêm entity
	Entity& addEntity()
	{
		Entity* e = new Entity;
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));

		return *e;
	}
	// xóa entity không hoạt động
	void refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](Entity* mEntity) {
				return !mEntity->isActive();
			}), std::end(entities));
	}
};