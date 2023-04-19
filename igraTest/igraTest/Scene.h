#ifndef SCENE_H

#define SCENE_H

#include "Entity.hpp"
#include <map>

class Scene
{
	
private:
	int id_count = 0;
	std::map<int, std::shared_ptr<Entity>> entities;

public:

	void AddEntity(const Entity& entity);
	std::shared_ptr<Entity> GetEntity(int id);
};

#endif // !SCENE_H

