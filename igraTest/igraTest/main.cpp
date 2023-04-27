#include<iostream>
#include<vector>
#include<cmath>

#include "raylib.h"
#include "MusicSystem.hpp"
#include "BackgroundManager_Horizontal.hpp"
#include "BackgroundManager_Vertical.hpp"
#include "Definitions.hpp"
#include "Scene.hpp"

#include "Components.h"
#include "Systems.h"


void Update(MusicSystem &musicSystem, BackgroundManager_Vertical &backgroundManagerV, Scene &scene, EntityDrawer &entityDrawer, 
			AnimationSystem &animationSystem, InputSystem &inputSystem)
{	
	if(IsKeyPressed(KEY_P))
	{
		musicSystem.SetPause();
	}
	if (IsKeyDown(KEY_S))
	{
		backgroundManagerV.SetCurrentSpeed(max(backgroundManagerV.GetCurrentSpeed() - 3.f*GetFrameTime(), 0.f));
	}
	if (IsKeyDown(KEY_W))
	{
		backgroundManagerV.SetCurrentSpeed(min(backgroundManagerV.GetCurrentSpeed() + 3.f*GetFrameTime(), 20.f));
	}
	/*if (IsKeyDown(KEY_D))
	{
		scene.GetEntity(0)->GetComponent<TransformComponent>()->mem_rotation += 2.f;
	}
	if (IsKeyDown(KEY_A))
	{
		scene.GetEntity(0)->GetComponent<TransformComponent>()->mem_rotation -= 2.f;
	}*/
	
	
	//audio
	musicSystem.UpdateMusic();
	//!audio

	backgroundManagerV.UpdateTexturePositionValues();

	//test
	
	animationSystem.On_Update_Animate();
	inputSystem.On_Update_Input();
	
	//!test
	
	//video
	BeginDrawing();

		ClearBackground(WHITE);

		backgroundManagerV.UpdateTexturePositions();
		scene.GetEntity(0)->GetComponent<TransformComponent>()->mem_position.x = GetMouseX();

		//test
		
		entityDrawer.On_Update_Draw();
		
		
		//!test
		
		DrawText("Hayo", GetScreenWidth() / 2, GetScreenHeight() / 2, 36, BLACK);

	EndDrawing();
}


int main()
{
	//initialize

	//window
	const int screenWidth = GetScreenWidth();
	const int screenHeight = GetScreenHeight();

	int targetFPS = 60;
	bool shouldBeFullscreen = true;

	//InitWindow(screenWidth, screenHeight, "Game");
	InitWindow(1200, 800, "Game");
	SetTargetFPS(targetFPS);
	//ToggleFullscreen();
	//!window

	//audio
	InitAudioDevice();
	std::vector<std::string> musicFilePaths = { "..\\..\\res\\as it was.wav", "..\\..\\res\\cinema.wav", "..\\..\\res\\daydreaming.wav" };

	MusicSystem musicSystem;
	musicSystem.LoadMusicFiles(musicFilePaths);
	musicSystem.InitMusicStreams(0.f);
	//!audio

	//background
	std::vector<TextureFilePath_ScrollingSpeed_Tuple> backgroundTuples = { {"..\\..\\res\\assets\\used\\Blue_Nebula_02-1024x1024.png", 1.f} };
	BackgroundManager_Vertical backgorundManagerV;
	backgorundManagerV.SetCurrentSpeed(3.f);
	backgorundManagerV.SetPrioritizeHeight(false);
	backgorundManagerV.LoadTextures(backgroundTuples);
	//!background

	//sprite

	std::shared_ptr<InputMappings> mappings= std::make_shared<InputMappings>(InputMappings{});
	mappings->mem_Map.AddAction("rotate_right", KEY_D, Down);
	mappings->mem_Map.AddAction("rotate_left", KEY_A, Down);


	Scene s1;

	Entity e1;

	e1.AddComponent<TransformComponent>()->Initialize({ GetScreenWidth() / 2.f, GetScreenHeight() / 1.25f }, 0.f, false, false, 1.f);

	e1.AddComponent<SpriteComponent>()->Initialize(
		LoadTexture("..\\..\\res\\assets\\used\\edited\\base.png"), 4, 2, 3.f);
	e1.AddComponent<AnimationComponent>()->Initialize(std::make_shared<AdvancedLoopAnimationScript>(AdvancedLoopAnimationScript({}, {})));
	
	e1.GetComponent<AnimationComponent>()->GetScript()->mem_LinkedProperties.AddVariable("frameSpeed", backgorundManagerV.GetCurrentSpeedPtr());
	
	e1.AddComponent<InputComponent>()->Initialize(std::make_shared<RotateInputScript>(RotateInputScript()), mappings);

	s1.AddEntity(e1);


	EntityDrawer entityDrawer(s1.GetVector());
	AnimationSystem animationSystem(s1.GetVector());
	InputSystem inputSystem(s1.GetVector());
	//!sprite

	//!initialize

	HideCursor();
	//game loop
	while (!WindowShouldClose())
	{
		Update(musicSystem, backgorundManagerV, s1, entityDrawer, animationSystem, inputSystem);
	}
	//!game loop


	//de-initialize
	CloseWindow();
	musicSystem.De_initMusics();
	backgorundManagerV.De_init();
	
	CloseAudioDevice();
	//!de-initialize

	return 0;
}