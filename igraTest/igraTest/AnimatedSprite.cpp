#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const Texture2D& texture, int spriteCount, float frameSpeed, const Vector2& position)
{
	spriteTexture = texture;
	this->spriteCount = spriteCount;
	frameCounter = 0;
	this->frameSpeed = frameSpeed;
	this->position = position;
	currentSpriteRectangle = { 0.f, 0.f, (float)texture.width / (float)spriteCount, (float)texture.height };
}

AnimatedSprite::AnimatedSprite(float frameSpeed, const Vector2& position)
{
	this->frameSpeed = frameSpeed;
	this->position = position;
}

void AnimatedSprite::LoadTexture(const std::string& filePath, int spriteCount)
{
	spriteTexture = ::LoadTexture(filePath.c_str());
	this->spriteCount = spriteCount;
	currentSpriteRectangle = { 0.f, 0.f, (float)spriteTexture.width / (float)spriteCount, (float)spriteTexture.height};
	
}

void AnimatedSprite::UpdateAnimatedSprite()
{
	frameCounter++;
	if (frameCounter >= (GetFPS() / frameSpeed))
	{
		frameCounter = 0;
		currentSprite++;

		if (currentSprite > spriteCount) currentSprite = 0;
	}
	currentSpriteRectangle.x = (float)(currentSprite)* (float)spriteTexture.width / (float)spriteCount;
}

void AnimatedSprite::DrawAnimatedSprite()
{
	DrawTextureRec(spriteTexture, currentSpriteRectangle, position, WHITE);
}

void AnimatedSprite::UpdatePosition(const Vector2& value)
{
	position = value;
}

Vector2 AnimatedSprite::GetPosition()
{
	return position;
}

void AnimatedSprite::De_init()
{
	UnloadTexture(spriteTexture);
}

void AnimatedSprite::SetFrameSpeed(float frameSpeed)
{
	this->frameSpeed = frameSpeed;
}

float AnimatedSprite::GetFrameSpeed()
{
	return frameSpeed;
}