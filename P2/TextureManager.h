#pragma once
#include <unordered_map>
#include "ThreadPool.h"

#include "SFML/Graphics.hpp"
class IExecutionEvent;
class TextureManager
{
public:
	typedef std::string String;
	typedef std::vector<sf::Texture*> TextureList;
	typedef std::unordered_map<String, TextureList> HashTable;

public:
	static TextureManager* getInstance();
	void loadFromAssetList(); //loading of all assets needed for startup
	void loadStreamingAssets();
	void loadSingleStreamAsset(int index, IExecutionEvent* executionEvent); //loads a single streaming asset based on index in directory
	sf::Texture* getFromTextureMap(const String assetName, int frameIndex);
	int getNumFrames(const String assetName);

	sf::Texture* getStreamTextureFromList(const int index);
	int getNumLoadedStreamTextures() const;
	void instantiateAsTexture(String path, String assetName, bool isStreaming);

	int streamingAssetCount = 0;

private:
	TextureManager();
	TextureManager(TextureManager const&) {};             // copy constructor is private
	TextureManager& operator=(TextureManager const&) {};  // assignment operator is private
	static TextureManager* sharedInstance;

	HashTable textureMap;
	TextureList baseTextureList;
	TextureList streamTextureList;
	ThreadPool* threadPool = new ThreadPool("newThread", 8);

	const std::string STREAMING_PATH = "Media/Streaming/";

	void countStreamingAssets();

};