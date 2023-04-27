#ifndef SPRITE_COMPONENT_HPP

#define SPRITE_COMPONENT_HPP

#include "Component.hpp"

class SpriteComponent : public Component
{
	
public:
	Texture2D mem_texture = { 0 };

	int mem_frameCountX = 1; //static
	int mem_frameCountY = 1;

	float mem_textureScale = 1.f;

	Rectangle mem_currentFrameRectangle = {};

	//using Component::Component;

	
	void Initialize(const Texture2D& texture, int frameCountX, int frameCountY, float textureScale)
	{
		mem_texture = texture;
		mem_frameCountX = frameCountX;
		mem_frameCountY = frameCountY;
		mem_textureScale = textureScale;

		mem_currentFrameRectangle = { 0.f, 0.f, (float)mem_texture.width / (float)mem_frameCountX, (float)mem_texture.height / (float)mem_frameCountY};
	}
};



#endif // !SPRITE_COMPONENT_HPP

