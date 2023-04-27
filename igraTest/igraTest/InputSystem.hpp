#ifndef INPUT_SYSTEM_HPP

#define INPUT_SYSTEM_HPP

#include "Entity.hpp"
#include "Components.h"
#include <vector>
#include "Definitions.hpp"

class InputSystem
{

	std::vector<std::shared_ptr<Entity>> mem_entities;

public:

	InputSystem(const std::vector<std::shared_ptr<Entity>>& entities)
	{
		mem_entities = entities;
	}
	void On_Update_Input()
	{
		for (std::shared_ptr<Entity>& e : mem_entities)
		{
			if (!(e->HasComponent<InputComponent>())) return;


			std::shared_ptr<InputComponent> input = e->GetComponent<InputComponent>();


			input->On_Update();

		}
	}
};

#endif // !INPUT_SYSTEM_HPP

