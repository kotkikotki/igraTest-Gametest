#ifndef TRANSFORM_COMPONENT_H

#define TRANSFORM_COMPONENT_H

#include "Component.h"

class TransformComponent : public Component
{
public:
	Vector2 mem_position = {0};
	float mem_rotation = 0.f;
	bool mem_flipVertical = false;
	bool mem_flipHorizontal = false;
	float mem_scale = 1.f;

	void Initialize(const Vector2& position, float rotation, bool flipVertical, bool flipHorizontal, float scale)
	{
		mem_position = position;
		mem_rotation = rotation;
		mem_flipVertical = flipVertical;
		mem_flipHorizontal = flipHorizontal;
		mem_scale = scale;
	}
};


#endif // !TRANSFORM_COMPONENT_H

