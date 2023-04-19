#ifndef SCENE_H

#define SCENE_H

#include "Entity.hpp"
#include <vector>

class Scene
{
	
private:

	std::vector<std::shared_ptr<Entity>> entities;

public:

	void AddEntity(const Entity& entity);
	std::shared_ptr<Entity> GetEntity(int id);
	std::vector<std::shared_ptr<Entity>>& GetVector();

};

#endif // !SCENE_H

