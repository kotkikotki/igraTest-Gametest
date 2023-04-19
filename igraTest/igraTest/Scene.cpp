#include "Scene.h"

void Scene::AddEntity(const Entity& entity)
{
	entities.insert(std::make_pair(id_count++, std::make_shared<Entity>(entity)));
}

std::shared_ptr<Entity> Scene::GetEntity(int id)
{
	return entities[id];
	
}