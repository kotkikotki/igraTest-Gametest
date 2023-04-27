#ifndef INPUT_COMPONENT_HPP

#define INPUT_COMPONENT_HPP

#include "Components.h"
#include "Definitions.hpp"

class InputMappings
{
	
	
public:

	Input_Action_Tuple_Map mem_Map;

	InputMappings(const std::initializer_list<std::pair<std::string, std::pair<int, KeyCondition>>> actions)
	{
		for (auto pair : actions)
		{
			mem_Map.AddAction(pair.first, pair.second.first, pair.second.second);
		}
	}
};

class InputScript
{

public:
	virtual void ProcessInput(const std::shared_ptr<InputMappings>& mappings, const std::shared_ptr<Entity>& owner)
	{
		
	}

};

class InputComponent : public Component
{

	std::shared_ptr<InputScript> mem_InputScript = std::make_shared<InputScript>(InputScript());
	std::shared_ptr<InputMappings> mem_InputMappings = std::make_shared<InputMappings>(InputMappings({}));

	std::shared_ptr<Entity> mem_Owner;
public:

	void Initialize(const std::shared_ptr<InputScript>& script, const std::shared_ptr<InputMappings>& mappings)
	{
		mem_InputScript = script;
		mem_InputMappings = mappings;

		const std::shared_ptr<Entity>& owner = GetOwner();


		mem_Owner = (owner == nullptr) ? std::make_shared<Entity>() : owner;
	}

	void On_Update()
	{
		mem_InputScript->ProcessInput(mem_InputMappings, mem_Owner);
	}

	std::shared_ptr<InputScript>& GetScript()
	{
		return mem_InputScript;
	}
};

class RotateInputScript : public InputScript
{
public:

	void ProcessInput(const std::shared_ptr<InputMappings>& mappings, const std::shared_ptr<Entity>& owner)
	{
		const std::shared_ptr<TransformComponent>& transform = owner->GetComponent<TransformComponent>();

		if (mappings->mem_Map.GetActionState("rotate_right"))
			transform->mem_rotation += 2.f;
		if (mappings->mem_Map.GetActionState("rotate_left"))
			transform->mem_rotation -= 2.f;
	}

};


#endif // !INPUT_COMPONENT_HPP

