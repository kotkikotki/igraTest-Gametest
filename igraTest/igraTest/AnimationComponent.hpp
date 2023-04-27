#ifndef ANIMATION_COMPONENT_HPP

#define ANIMATION_COMPONENT_HPP

#include<map>

#include "Component.hpp"
#include "SpriteComponent.hpp"
#include "Definitions.hpp"

class AnimationScript
{
	
public:

	Name_Variable_Tuple_Map mem_Properties;
	Name_LinkedVariable_Tuple_Map mem_LinkedProperties;

	//Rectangle mem_currentFrameRectangle = {};
	explicit AnimationScript(const std::initializer_list < std::pair<std::string, std::any>>& properties, const std::initializer_list < std::pair<std::string, std::shared_ptr<std::any>>>& linkedProperties)
	{
		for (auto pair : properties)
		{
			mem_Properties.AddVariable(pair.first, pair.second);
		}
		for (auto pair : linkedProperties)
		{
			mem_LinkedProperties.AddVariable(pair.first, pair.second);
		}

	}

	virtual void Animate(const std::shared_ptr<SpriteComponent>& sprite) {}

	virtual void UpdateProperties() {}

	virtual void AddProperties(const std::initializer_list < std::pair<std::string, std::string>>& properties, const std::initializer_list < std::pair<std::string, std::shared_ptr<std::any>>>& linkedProperties)
	{
		for (auto pair : properties)
		{
			mem_Properties.AddVariable(pair.first, pair.second);
		}
		for (auto pair : linkedProperties)
		{
			mem_LinkedProperties.AddVariable(pair.first, pair.second);
		}

	}

	
};

class AnimationComponent : public Component
{

	
	std::shared_ptr<AnimationScript> mem_AnimationScript = std::make_shared<AnimationScript>(AnimationScript({},{}));
	//req
	std::shared_ptr<SpriteComponent> mem_SpriteComponent;

	//using Component::Component;

public:
	void Initialize(const std::shared_ptr<AnimationScript>& script)
	{
		mem_AnimationScript = script;

		const std::shared_ptr<SpriteComponent>& sprite = GetOwner()->GetComponent<SpriteComponent>();
		

		mem_SpriteComponent = (sprite == nullptr)? std::make_shared<SpriteComponent>(): sprite;
		
		
		//mem_SpriteComponent->mem_currentFrameRectangle = { 0.f, 0.f, (float)mem_SpriteComponent->mem_texture.width / (float)sprite->mem_frameCount, (float)mem_SpriteComponent->mem_texture.height };
	}

	void On_Update()
	{
		mem_AnimationScript->UpdateProperties();
		mem_AnimationScript->Animate(mem_SpriteComponent);
		
	}

	std::shared_ptr<AnimationScript>& GetScript()
	{
		return mem_AnimationScript;
	}

	

};

//Scripts

class LoopAnimationScript : public AnimationScript
{
public:

	float mem_frameSpeed = 1.f;
	int mem_currentFrame = 0;
	int mem_frameCounter = 0;

	using AnimationScript::AnimationScript;

	void Animate(const std::shared_ptr<SpriteComponent>& sprite) override
	{
		mem_frameCounter++;
		if (mem_frameCounter >= (GetFPS() / mem_frameSpeed))
		{
			mem_frameCounter = 0;
			mem_currentFrame++;

			if (mem_currentFrame >= (sprite->mem_frameCountX * sprite->mem_frameCountY)) mem_currentFrame = 0;
		}

		int currentFrameX = mem_currentFrame % sprite->mem_frameCountX,
			currentFrameY = mem_currentFrame / sprite->mem_frameCountX;
		

		sprite->mem_currentFrameRectangle.x = (float)(currentFrameX) * (float)sprite->mem_texture.width  / (float)(sprite->mem_frameCountX);
		sprite->mem_currentFrameRectangle.y = (float)(currentFrameY) * (float)sprite->mem_texture.height / (float)(sprite->mem_frameCountY);
	}

	void UpdateProperties() override
	{
		//frameSpeed
		if (!mem_LinkedProperties.HasVariable("frameSpeed")) return;

		//mem_frameSpeed = mem_LinkedProperties.GetVariablePtr<float>("frameSpeed");
		mem_frameSpeed = *std::static_pointer_cast<float>(mem_LinkedProperties.GetVariablePtr("frameSpeed"));
	}

};

class AdvancedLoopAnimationScript : public AnimationScript
{
public:


	int mem_currentFrame = 0;
	int mem_frameCounter = 0;

	//
	float mem_frameSpeed = 1.f;

	using AnimationScript::AnimationScript;


	void Animate(const std::shared_ptr<SpriteComponent>& sprite) override
	{
		int currentFrameMin = (mem_frameSpeed>=4.f) ? sprite->mem_frameCountX : 0;
		int currentFrameMax = (mem_frameSpeed >= 4.f) ? sprite->mem_frameCountX * sprite->mem_frameCountY : sprite->mem_frameCountX;
		mem_frameCounter++;
		if (mem_frameCounter >= (GetFPS() / mem_frameSpeed))
		{
			mem_frameCounter = 0;
			mem_currentFrame++;

			if (mem_currentFrame >= currentFrameMax) mem_currentFrame = currentFrameMin;
		}

		int currentFrameX = mem_currentFrame % sprite->mem_frameCountX,
			currentFrameY = mem_currentFrame / sprite->mem_frameCountX;


		sprite->mem_currentFrameRectangle.x = (float)(currentFrameX) * (float)sprite->mem_texture.width / (float)(sprite->mem_frameCountX);
		sprite->mem_currentFrameRectangle.y = (float)(currentFrameY) * (float)sprite->mem_texture.height / (float)(sprite->mem_frameCountY);
	}

	void UpdateProperties() override
	{
		if (!mem_LinkedProperties.HasVariable("frameSpeed")) return;

		//mem_frameSpeed = mem_LinkedProperties.GetVariable<float>("frameSpeed");
		mem_frameSpeed = *std::static_pointer_cast<float>(mem_LinkedProperties.GetVariablePtr("frameSpeed"));

	}

};




#endif // !ANIMATION_COMPONENT_HPP

