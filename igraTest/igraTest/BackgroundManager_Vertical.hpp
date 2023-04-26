#ifndef BACKGROUND_MANAGER_VERTICAL_HPP

#define BACKGROUND_MANAGER_VERTICAL_HPP

#include<stdexcept>
#include<string>
#include<vector>
#include "raylib.h"
#include "Definitions.hpp"

class BackgroundManager_Vertical
{

	std::vector<Texture_ScrollingSpeed_Tuple> backgroundTextures; //order - from back to front
	std::vector<float> textureScrollPositions;

	int size = 0;

	float overallSpeedMultiplier = 0.f;

	//req
	
	std::shared_ptr<float> overallSpeedMultiplierPtr = std::make_shared<float>(overallSpeedMultiplier);
	
	//
	


	//
	const float maxSpeed = 100.f;
	//
	bool prioritizeHeight = true;

public:

	//
	

	void LoadTextures(const std::vector<std::string>& imageFilePaths, const std::vector<float>& scrollingSpeeds)
	{
		if (imageFilePaths.size() != scrollingSpeeds.size()) throw std::invalid_argument("Invalid background textures arguments.");

		int n = imageFilePaths.size();
		for (int i = 0; i < n; i++)
		{
			Texture_ScrollingSpeed_Tuple tuple;
			tuple.texture = LoadTexture(imageFilePaths[i].c_str());
			tuple.scrollingSpeed = scrollingSpeeds[i];

			backgroundTextures.push_back(tuple);
			textureScrollPositions.push_back(0.f);
		}
		size = n;
	}

	void LoadTextures(const std::vector<TextureFilePath_ScrollingSpeed_Tuple>& backgroundTuples)
	{
		int n = backgroundTuples.size();
		for (int i = 0; i < n; i++)
		{
			Texture_ScrollingSpeed_Tuple tuple;
			tuple.texture = LoadTexture(backgroundTuples[i].filePath.c_str());
			tuple.scrollingSpeed = backgroundTuples[i].scrollingSpeed;

			backgroundTextures.push_back(tuple);
			textureScrollPositions.push_back(0.f);
		}
		size = n;
	}
	void UpdateTexturePositionValues()
	{
		for (int i = 0; i < size; i++)
		{

			if (-overallSpeedMultiplier >= 0.f)
			{
				textureScrollPositions[i] -= backgroundTextures[i].scrollingSpeed * -overallSpeedMultiplier;
				if (textureScrollPositions[i] <= -GetRenderHeight()) textureScrollPositions[i] = 0.f;
			}
			else
			{
				textureScrollPositions[i] -= backgroundTextures[i].scrollingSpeed * -overallSpeedMultiplier;
				if (textureScrollPositions[i] >= GetRenderHeight()) textureScrollPositions[i] = 0.f;
			}
		}
	}
	void UpdateTexturePositions()
	{
		for (int i = 0; i < size; i++)
		{

			Vector2 pos1 = { 0.f, textureScrollPositions[i] };
			Vector2 pos2 = { 0.f, (GetRenderHeight() + textureScrollPositions[i]) };
			Vector2 pos0 = { 0.f, (-GetRenderHeight() + textureScrollPositions[i]) };



			DrawTexturePro(backgroundTextures[i].texture, { 0.f, 0.f, (float)backgroundTextures[i].texture.width, (float)backgroundTextures[i].texture.height },
				{ pos1.x, pos1.y, (float)GetRenderWidth(), (float)GetRenderHeight() }, { 0.f, 0.f }, 0.f, WHITE);
			DrawTexturePro(backgroundTextures[i].texture, { 0.f, 0.f, (float)backgroundTextures[i].texture.width, (float)backgroundTextures[i].texture.height },
				{ pos2.x, pos2.y, (float)GetRenderWidth(), (float)GetRenderHeight() }, { 0.f, 0.f }, 0.f, WHITE);
			DrawTexturePro(backgroundTextures[i].texture, { 0.f, 0.f, (float)backgroundTextures[i].texture.width, (float)backgroundTextures[i].texture.height },
				{ pos0.x, pos0.y, (float)GetRenderWidth(), (float)GetRenderHeight() }, { 0.f, 0.f }, 0.f, WHITE);
		}
	}
	void De_init()
	{
		for (Texture_ScrollingSpeed_Tuple& t : backgroundTextures)
		{
			UnloadTexture(t.texture);
		}
	}

	void SetCurrentSpeed(float speed)
	{
		float newSpeed = speed;
		if (newSpeed < 0.f) newSpeed = 0.f;
		overallSpeedMultiplier = speed;

		//
		*overallSpeedMultiplierPtr = overallSpeedMultiplier;
	}

	float GetCurrentSpeed()
	{
		return overallSpeedMultiplier;
	}

	const std::shared_ptr<float>& GetCurrentSpeedPtr()
	{
		return overallSpeedMultiplierPtr;
	}

	

	void SetPrioritizeHeight(bool value)
	{
		prioritizeHeight = value;
	}
	bool GetPrioritizeHeight()
	{
		return prioritizeHeight;
	}
};


#endif // !BACKGROUND_MANAGER_VERTICAL_HPP

