#include "AudioManager.h"

#include <filesystem>

#include "TextureManager.h"
#include <vector>

#include "AudioLoader.h"
#include "IExecutionEvent.h"
#include "StringUtils.h"
namespace fs = std::filesystem;

AudioManager* AudioManager::sharedInstance = NULL;

AudioManager* AudioManager::getInstance()
{
	if (sharedInstance == NULL)
	{
		sharedInstance = new AudioManager();

	}
	return sharedInstance;
}



AudioManager::AudioManager(String path, IExecutionEvent* executionEvent)
{
	this->path = path;
	this->execEvent = executionEvent;

}

AudioManager::AudioManager()
{
	int count = std::distance(fs::directory_iterator(STREAMING_PATH), fs::directory_iterator{});
	totalAssets = totalAssets + count;

	this->threadPool->startScheduler();

}

AudioManager::~AudioManager()
{

}

void AudioManager::loadAll(String path, IExecutionEvent* executionEvent)
{

	int fileNum = 0;
	int index = 0;
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		if (index == fileNum)
		{
			//simulate loading of very large file
			//<code here for thread sleeping. Fill this up only when instructor told so.>


			//<code here for loading asset>
			String assetName = "";
			//std::u8string path_string = entry.path().u8string();

			//StreamAssetLoader* assetLoader = new StreamAssetLoader(entry.path().string(), executionEvent);

			//assetLoader->start();


			//threadPool->scheduleTask(assetLoader);

			//this->instantiateAsTexture(entry.path().string(), assetName, true);
			//std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
			break;
		}

		fileNum++;
	}


}

void AudioManager::LoadAudio(int index, IExecutionEvent* executionEvent)
{
	int fileNum = 0;


	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		if (index == fileNum)
		{
			//simulate loading of very large file
			//<code here for thread sleeping. Fill this up only when instructor told so.>


			//<code here for loading asset>

			String path = entry.path().generic_string();
			std::vector<String> tokens = StringUtils::split(path, '/');
			String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];


			std::cout << assetName <<" sound"<< std::endl;

			//std::u8string path_string = entry.path().u8string();

			AudioLoader* audioLoader = new AudioLoader(entry.path().string(), executionEvent, assetName);

			//assetLoader->start();

			threadPool->scheduleTask(audioLoader);

			//this->instantiateAsTexture(entry.path().string(), assetName, true);
			//std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
			break;
		}

		fileNum++;
	}


}

void AudioManager::loadBuffer(std::string key, std::string path)
{


	sf::SoundBuffer* soundBuffer = new sf::SoundBuffer;
	soundBuffer->loadFromFile(path);
	BufferMap[key] = soundBuffer;
	sf::Sound* sound = new sf::Sound;
	//sf::SoundBuffer* m_soundBuffer;
	//m_soundBuffer = AudioManager::getInstance()->getBuffer(key);
	//sound->setBuffer(*m_soundBuffer);

	sound->setBuffer(*AudioManager::getInstance()->getBuffer(key));
	sound->setVolume(20);
	soundMap[key].push_back(sound);

	soundList.push_back(sound);

	std::cout << "loaded" << std::endl;

}

sf::SoundBuffer* AudioManager::getBuffer(std::string key)
{
	if (BufferMap[key] != NULL)
	{
		return BufferMap[key];
	}
	else {

		std::cerr << "error" << std::endl;
		return NULL;
	}
}

std::vector<sf::Sound*> AudioManager::getSoundList()
{
	return this->soundList;

}
