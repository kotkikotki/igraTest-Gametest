#ifndef ENTITY_DRAWER_H

#define ENTITY_DRAWER_H

#include "Entity.hpp"
#include "Components.h"
#include <vector>
#include "Definitions.hpp"

class EntityDrawer
{

	std::vector<std::shared_ptr<Entity>> mem_entities;

public:
	EntityDrawer(const std::vector<std::shared_ptr<Entity>> &entities)
	{
		mem_entities = entities;
	}
	void On_Update_Draw()
	{
		for (std::shared_ptr<Entity> e: mem_entities)
		{
			if (!(e->HasComponent<SpriteComponent>() && e->HasComponent<TransformComponent>())) return;
			
			/*DrawTextureRec(e->GetComponent<SpriteComponent>()->mem_texture,
						   e->GetComponent<SpriteComponent>()->mem_currentFrameRectangle,
						   e->GetComponent<TransformComponent>()->mem_position, WHITE);*/
			std::shared_ptr<SpriteComponent> sprite = e->GetComponent<SpriteComponent>();
			std::shared_ptr<TransformComponent> transform = e->GetComponent<TransformComponent>();



			DrawTexturePro(sprite->mem_texture, sprite->mem_currentFrameRectangle,
				{ transform->mem_position.x, transform->mem_position.y, sprite->mem_currentFrameRectangle.width * sprite->mem_textureScale, sprite->mem_currentFrameRectangle.height * sprite->mem_textureScale },
				{ sprite->mem_currentFrameRectangle.width* SQRT2, sprite->mem_currentFrameRectangle.height* SQRT2 }, transform->mem_rotation, WHITE);
			
		}
	}
};


#endif // !ENTITY_DRAWER_H
