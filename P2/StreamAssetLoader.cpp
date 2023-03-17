#include "StreamAssetLoader.h"
#include "TextureManager.h"

#include <vector>

#include "IExecutionEvent.h"

StreamAssetLoader::StreamAssetLoader(String path, String assetName, IExecutionEvent* executionEvent)
{
	this->path = path;
	this->assetName = assetName;
	this->execEvent = executionEvent;

}

StreamAssetLoader::~StreamAssetLoader()
{

}

void StreamAssetLoader::onStartTask()
{
	//IETThread::sleep(1000);
	TextureManager::getInstance()->instantiateAsTexture(this->path, this->assetName, true);



	this->execEvent->onFinishedExecution(this->assetName);
	delete this;
}
