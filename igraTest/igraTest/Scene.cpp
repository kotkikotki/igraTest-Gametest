#include "Scene.h"

void Scene::AddEntity(const Entity& entity)
{
	entities.push_back(std::make_shared<Entity>(entity));
}

std::shared_ptr<Entity> Scene::GetEntity(int id)
{
	return entities[id];
	
}

std::vector<std::shared_ptr<Entity>>& Scene::GetVector()
{
	return entities;
}