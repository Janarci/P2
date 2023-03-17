#pragma once
#include "IETThread.h"
#include "IWorkerAction.h"
class IExecutionEvent;
class StreamAssetLoader: public IWorkerAction
{

private: typedef std::string String;

public:
	StreamAssetLoader(String path, String assetName, IExecutionEvent* executionEvent);
	~StreamAssetLoader();

private:
	void onStartTask() override;


	String path;
	String assetName;
	IExecutionEvent* execEvent;
};

