#ifndef BACKGROUND_MANAGER_HORIZONTAL_H

#define BACKGROUND_MANAGER_HORIZONTAL_H

#include<string>
#include<vector>
#include "raylib.h"
#include "Definitions.hpp"

class BackgroundManager_Horizontal
{

	std::vector<Texture_ScrollingSpeed_Tuple> backgroundTextures; //order - from back to front
	std::vector<float> textureScrollPositions;

	int size = 0;

	float overallSpeedMultiplier = 0.f;

	//
	const float maxSpeed = 100.f;
	//

	bool prioritizeHeight = true;

public:

	void LoadTextures(const std::vector<std::string> &imagesFilePaths, const std::vector<float> &scrollingSpeeds);

	void LoadTextures(const std::vector<TextureFilePath_ScrollingSpeed_Tuple> &backgroundTuples);

	void UpdateTexturePositionValues();

	void UpdateTexturePositions();

	void De_init();

	void SetCurrentSpeed(float speed);

	float GetCurrentSpeed();

	void SetPrioritizeHeight(bool value);

	bool GetPrioritizeHeight();
};


#endif // !BACKGROUND_MANAGER_HORIZONTAL_H

