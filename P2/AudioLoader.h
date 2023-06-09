#pragma once
#include "IETThread.h"
#include "IWorkerAction.h"

#include "AudioManager.h"

class IExecutionEvent;
class AudioLoader : public IWorkerAction
{

private: typedef std::string String;

public:
	AudioLoader(String path, IExecutionEvent* executionEvent, String assetName);
	~AudioLoader();

private:
	void onStartTask() override;


	String path;
	IExecutionEvent* execEvent;
	String assetName;
};
