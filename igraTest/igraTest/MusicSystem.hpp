#ifndef MUSIC_SYSTEM_HPP

#define MUSIC_SYSTEM_HPP

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

	void LoadMusicFiles(const std::vector<std::string>& musicFilePaths)
	{
		for (std::string filePath : musicFilePaths)
		{
			Music music = LoadMusicStream(filePath.c_str());
			musicStreams.push_back(music);
		}
	}

	void InitMusicStreams(float volume)
	{
		MusicSystem::volume = volume;
		pause = 0;
		isPaused = 0;
		currentIndex = 0;
		PlayMusicStreams(currentIndex);
	}

	void PlayMusicStreams(int index)
	{
		PlayMusicStream(musicStreams[index]);
		SetMusicVolume(musicStreams[index], volume);
	}

	void UpdateMusic()
	{
		//check for pause
		if (pause && !isPaused)
		{
			PauseMusicStream(musicStreams[currentIndex]);
			isPaused = true;
			return;
		}
		if (!pause)
		{
			if (isPaused)
			{
				ResumeMusicStream(musicStreams[currentIndex]);
				isPaused = false;
			}
		}


		int index = currentIndex;

		float timePassed = GetMusicTimePlayed(musicStreams[currentIndex]) + GetFrameTime() * 3;

		if (timePassed >= GetMusicTimeLength(musicStreams[currentIndex]))
		{
			ChangeMusic();
			return;
		}

		UpdateMusicStream(musicStreams[currentIndex]);
	}

	void De_initMusic(int index)
	{
		StopMusicStream(musicStreams[index]);
	}

	void De_initMusics()
	{
		for (const Music& music : musicStreams)
		{
			if (IsMusicStreamPlaying(music) || IsMusicReady(music))
			{
				StopMusicStream(music);
				UnloadMusicStream(music);
			}
		}
	}

	void ChangeMusic()
	{
		int prevIndex = currentIndex;
		int newIndex = prevIndex + 1;

		//clamp
		if (newIndex >= musicStreams.size())
			newIndex = 0;

		De_initMusic(prevIndex);
		PlayMusicStreams(newIndex);

		this->currentIndex = newIndex;

	}

	void SetPause()
	{
		pause = !pause;
	}

	void SetVolume(float newVolume)
	{
		SetMusicVolume(musicStreams[currentIndex], volume);
		volume = newVolume;
	}

	//for debug
	/*
	int MusicSystem::getCurrentIndex()
	{
		return currentIndex;
	}
	*/
};

#endif // !AUDIO_SYSTEM_HPP

