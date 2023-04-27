#ifndef ANIMATION_SYSTEM_HPP

#define ANIMATION_SYSTEM_HPP

#include "Entity.hpp"
#include "Components.h"
#include <vector>
#include "Definitions.hpp"

class AnimationSystem
{

	std::vector<std::shared_ptr<Entity>> mem_entities;

public:

	AnimationSystem(const std::vector<std::shared_ptr<Entity>>& entities)
	{
		mem_entities = entities;
	}
	void On_Update_Animate()
	{
		for (std::shared_ptr<Entity>& e : mem_entities)
		{
			if (!(e->HasComponent<AnimationComponent>())) return;

			
			std::shared_ptr<AnimationComponent> animation = e->GetComponent<AnimationComponent>();


			animation->On_Update();

		}
	}
};


#endif // !ANIMATION_SYSTEM_HPP
