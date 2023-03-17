#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"

class IconObject;
/// <summary>
/// Class that deals with displaying of streamed textures
/// </summary>
class TextureDisplay : public AGameObject, public IExecutionEvent
{
public:
	TextureDisplay();
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

	void onFinishedExecution(String assetName) override;
	void onFinishedExecutionSound() override;
	bool checkLoading();

private:
	typedef std::vector<IconObject*> IconList;
	IconList iconList;

	enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };
	const float STREAMING_LOAD_DELAY = 2500.0f;
	const StreamingType streamingType = SINGLE_STREAM;
	float ticks = 0.0f;
	bool startedStreaming = false;

	int AudioAssetsLoaded = 0;
	int ImageAssetsLoaded = 0;
	bool finishedLoadingAudio = false;
	bool finishedLoadingImage = false;

	bool finishedLoadingAll = false;

	int columnGrid = 0; int rowGrid = 0;
	int numDisplayed = 0;
	const int MAX_COLUMN = 28;
	const int MAX_ROW = 22;

	void spawnObject();
	void changeDisplay(String assetName);
	void playSound(String assetName);


private:
	bool onePressed = false;
	bool twoPressed = false;
	bool threePressed = false;
	bool fourPressed = false;
	bool fivePressed = false;
	bool sixPressed = false;
	bool sevenPressed = false;
	bool eightPressed = false;
	bool ninePressed = false;
};

