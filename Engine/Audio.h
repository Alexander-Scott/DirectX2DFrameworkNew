#pragma once

#include "DirectXTK\Inc\Audio.h"

#include <map>

// WHY IS THIS HERE AND NOT IN CONSTS.H????
static std::map<std::string, std::string> AudioFilePaths =
{
	{ "Whoosh",			"Audio\\Whoosh.wav"  },
	{ "GunShot",		"Audio\\GunShot.wav" },	
	{ "Jump",			"Audio\\Jump.wav"	 },
	{ "Death",			"Audio\\Death.wav" },
};

class Audio 
{
	friend class MainWindow;

public:
	Audio();
	~Audio();

	void Update();
	void Suspend();
	void Resume();

	void PlaySoundEffect(std::string name);

	void OnNewAudioDevice() { m_retryAudio = true; }
	void CreateSoundEffects();

	static Audio& Instance()
	{
		static Audio Instance;
		return Instance;
	}

private:
	std::unique_ptr<DirectX::AudioEngine> m_audEngine;
	std::map<std::string, std::unique_ptr<DirectX::SoundEffect>> m_audioFiles;
	bool m_retryAudio;
};