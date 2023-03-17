#pragma once
#include <unordered_map>
#include <SFML/Audio.hpp>

#include "IETThread.h"
#include "IWorkerAction.h"
#include "ThreadPool.h"



class IExecutionEvent;
class AudioManager
{
public:
	typedef std::string String;
	typedef std::vector<sf::Sound*> Sound;

	typedef std::unordered_map<std::string, Sound> SoundMap;

private:

	typedef std::string String;
	AudioManager(String path, IExecutionEvent* executionEvent);
	AudioManager();
	~AudioManager();

public:
	
	static  AudioManager* getInstance();
	void LoadAudio(int index, IExecutionEvent* executionEvent);
	void loadBuffer(std::string, std::string);

	std::vector<sf::Sound*> soundList;
	SoundMap soundMap;
	int totalAssets = 0;

private:

	static AudioManager* sharedInstance;
	void loadAll(String path, IExecutionEvent* executionEvent);
	sf::SoundBuffer* getBuffer(std::string);


	std::unordered_map<std::string, sf::SoundBuffer*> BufferMap;

	std::vector<sf::Sound*> getSoundList();

	ThreadPool* threadPool = new ThreadPool("AudioThread", 2);

	const std::string STREAMING_PATH = "Media/OST/wav";


	String path;
	IExecutionEvent* execEvent;
};

