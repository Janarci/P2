#include "AudioLoader.h"

#include <vector>

#include "IExecutionEvent.h"

AudioLoader::AudioLoader(String path, IExecutionEvent* executionEvent, String assetName)
{
	this->path = path;
	this->execEvent = executionEvent;
	this->assetName = assetName;

}

AudioLoader::~AudioLoader()
{

}

void AudioLoader::onStartTask()
{
	IETThread::sleep(3000);
	AudioManager::getInstance()->loadBuffer(this->assetName, this->path);

	this->execEvent->onFinishedExecutionSound();
	delete this;
}
