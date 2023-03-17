#include <fstream>
#include <iostream>
#include <filesystem>
#include "TextureManager.h"
#include "StringUtils.h"
#include "IETThread.h"
#include "StreamAssetLoader.h"

//a singleton class
TextureManager* TextureManager::sharedInstance = NULL;

TextureManager* TextureManager::getInstance() {
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new TextureManager();
	}

	return sharedInstance;
}

TextureManager::TextureManager()
{
	this->countStreamingAssets();
	this->threadPool->startScheduler();
}

void TextureManager::loadFromAssetList()
{
	std::cout << "[TextureManager] Reading from asset list" << std::endl;
	std::ifstream stream("Media/assets.txt");
	String path;

	while (std::getline(stream, path))
	{
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		this->instantiateAsTexture(path, assetName, false);
		std::cout << "[TextureManager] Loaded texture: " << assetName << std::endl;
	}
}

void TextureManager::loadStreamingAssets()
{
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		IETThread::sleep(200);

		String path = entry.path().generic_string();
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];

		this->instantiateAsTexture(path, assetName, true);

	}
}

void TextureManager::loadSingleStreamAsset(int index, IExecutionEvent* executionEvent)
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

			std::cout << assetName << std::endl;

			//std::u8string path_string = entry.path().u8string();

			StreamAssetLoader* assetLoader = new StreamAssetLoader(entry.path().string(), assetName, executionEvent);

			//assetLoader->start();


			threadPool->scheduleTask(assetLoader);

			//this->instantiateAsTexture(entry.path().string(), assetName, true);
			//std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
			break;
		}

		fileNum++;
	}
}

void TextureManager::loadSingleStreamAssetP2(int index, IExecutionEvent* executionEvent)
{
	int fileNum = 0;

	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		if (index == fileNum)
		{
			String assetName = "";
			std::cout << entry.path().string() << std::endl;

			StreamAssetLoader* assetLoader = new StreamAssetLoader(entry.path().string(), assetName, executionEvent);

			threadPool->scheduleTask(assetLoader);

			break;
		}

		fileNum++;
	}
}

sf::Texture* TextureManager::getFromTextureMap(const String assetName, int frameIndex)
{
	if (!this->textureMap[assetName].empty()) {
		return this->textureMap[assetName][frameIndex];
	}
	else {
		std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
		return NULL;
	}
}

int TextureManager::getNumFrames(const String assetName)
{
	if (!this->textureMap[assetName].empty()) {
		return this->textureMap[assetName].size();
	}
	else {
		std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
		return 0;
	}
}

sf::Texture* TextureManager::getStreamTextureFromList(const int index)
{
	return this->streamTextureList[index];
}

TextureManager::HashTable TextureManager::getTextureMap()
{
	return this->textureMap;
}

int TextureManager::getNumLoadedStreamTextures() const
{
	return this->streamTextureList.size();
}

void TextureManager::countStreamingAssets()
{
	this->streamingAssetCount = 0;
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		this->streamingAssetCount++;
	}
	std::cout << "[TextureManager] Number of streaming assets: " << this->streamingAssetCount << std::endl;
}

void TextureManager::instantiateAsTexture(String path, String assetName, bool isStreaming)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	this->textureMap[assetName].push_back(texture);

	if (isStreaming)
	{
		this->streamTextureList.push_back(texture);
	}
	else
	{
		this->baseTextureList.push_back(texture);
	}

}
