#ifndef ANIMATION_COMPONENT_H

#define ANIMATION_COMPONENT_H

#include<map>

#include "Component.h"
#include "SpriteComponent.hpp"
#include "Definitions.hpp"

class AnimationScript
{
	
public:

	Name_Variable_Tuple mem_Properties;
	Name_LinkedVariable_Tuple mem_LinkedProperties;

	//Rectangle mem_currentFrameRectangle = {};

	virtual void Animate(const std::shared_ptr<SpriteComponent>& sprite) {}

	virtual void AddLinkedProperty(const std::string& name, const std::string& value) 
	{ 
		mem_LinkedProperties.AddVariable(name, std::make_shared<std::string>(value));
	}

	virtual void UpdateProperties() {}

	
};

class AnimationComponent : public Component
{
public:
	
	std::shared_ptr<AnimationScript> mem_AnimationScript = std::make_shared<AnimationScript>(AnimationScript());
	//req
	std::shared_ptr<SpriteComponent> mem_SpriteComponent;


	void Initialize(const std::shared_ptr<AnimationScript>& script, const std::shared_ptr<SpriteComponent>& sprite)
	{
		mem_AnimationScript = script;
		mem_SpriteComponent = sprite;

		
		//mem_SpriteComponent->mem_currentFrameRectangle = { 0.f, 0.f, (float)mem_SpriteComponent->mem_texture.width / (float)sprite->mem_frameCount, (float)mem_SpriteComponent->mem_texture.height };
	}

	void On_Update()
	{
		mem_AnimationScript->UpdateProperties();
		mem_AnimationScript->Animate(mem_SpriteComponent);
		
	}

	std::shared_ptr<AnimationScript> GetScript()
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

	LoopAnimationScript()
	{
		mem_Properties.AddVariable("frameSpeed", std::to_string(mem_frameSpeed));
	}

	/*void AddLinkedProperty(const std::string& name, const std::string& value)
	{
		mem_LinkedProperties.AddVariable(name, std::make_shared<std::string>(value));
	}*/

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
		//mem_frameSpeed = std::stof(mem_Properties.pairs["frameSpeed"]);
		mem_frameSpeed = std::stof(*mem_LinkedProperties.pairs["frameSpeed"]);
	}

};

class AdvancedLoopAnimationScript : public AnimationScript
{
public:


	int mem_currentFrame = 0;
	int mem_frameCounter = 0;

	//
	float mem_frameSpeed = 1.f;

	AdvancedLoopAnimationScript()
	{
		mem_Properties.AddVariable("frameSpeed", std::to_string(mem_frameSpeed));
	}

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
		mem_frameSpeed = std::stof(mem_Properties.pairs["frameSpeed"]);
	}

};




#endif // !ANIMATION_COMPONENT_H

