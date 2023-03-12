#include "AudioLoader.h"

#include <vector>

#include "IExecutionEvent.h"

AudioLoader::AudioLoader(String path, IExecutionEvent* executionEvent, int key)
{
	this->path = path;
	this->execEvent = executionEvent;
	this->key = key;

}

AudioLoader::~AudioLoader()
{

}

void AudioLoader::onStartTask()
{
	IETThread::sleep(1000);
	//TextureManager::getInstance()->instantiateAsTexture(this->path, "wew", true);
	AudioManager::getInstance()->loadBuffer(std::to_string(this->key), this->path);

	this->execEvent->onFinishedExecution();
	delete this;
}
