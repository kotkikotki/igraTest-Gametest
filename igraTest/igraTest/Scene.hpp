#ifndef SCENE_HPP

#define SCENE_HPP

#include "Entity.hpp"
#include <vector>

class Scene
{
	
private:

	std::vector<std::shared_ptr<Entity>> entities;

public:


	void AddEntity(const Entity& entity)
	{
		entities.push_back(std::make_shared<Entity>(entity));
	}

	std::shared_ptr<Entity>& GetEntity(int id)
	{
		return entities[id];

	}

	void RemoveEntity(int id)
	{
		entities.erase(entities.begin() + id);

	}

	const std::vector<std::shared_ptr<Entity>>& GetVector()
	{
		return entities;
	}

};

#endif // !SCENE_HPP

