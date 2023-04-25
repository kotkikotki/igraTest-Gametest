#ifndef SCENE_H

#define SCENE_H

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

	std::shared_ptr<Entity> GetEntity(int id)
	{
		return entities[id];

	}

	std::vector<std::shared_ptr<Entity>>& GetVector()
	{
		return entities;
	}

};

#endif // !SCENE_H

