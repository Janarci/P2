#pragma once
#include <string>

class IExecutionEvent
{
public:
	virtual void onFinishedExecution(std::string assetName) = 0;
	virtual void onFinishedExecutionSound() = 0;
};
