#ifndef MUSIC_SYSTEM_H

#define MUSIC_SYSTEM_H

#include<raylib.h>
#include<vector>
#include<string>

class MusicSystem
{
	std::vector<Music> musicStreams;
	int currentIndex = 0;

	bool isPaused = false;
	bool pause = false;

	float volume = 1.f;

public:


	void LoadMusicFiles(const std::vector<std::string>& musicFilePaths);

	void InitMusicStreams(float volume);

	void PlayMusicStreams(int index);
	
	void UpdateMusic();
	
	void De_initMusic(int index);
	
	void De_initMusics();

	void ChangeMusic();

	void SetPause();

	void SetVolume(float newVolume);

	/*
	//for debug
	int getCurrentIndex();
	*/
};

#endif // !AUDIO_SYSTEM_H

