#include "StreamAssetLoader.h"
#include "TextureManager.h"

#include <vector>

#include "IExecutionEvent.h"

StreamAssetLoader::StreamAssetLoader(String path, IExecutionEvent* executionEvent)
{
	this->path = path;
	this->execEvent = executionEvent;

}

StreamAssetLoader::~StreamAssetLoader()
{

}

void StreamAssetLoader::onStartTask()
{
	//IETThread::sleep(1000);
	TextureManager::getInstance()->instantiateAsTexture(this->path, "wew", true);

	this->execEvent->onFinishedExecution();
	delete this;
}
