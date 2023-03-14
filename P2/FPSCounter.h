#pragma once
#include "AGameObject.h"
class FPSCounter : public AGameObject
{
public:
	FPSCounter();
	~FPSCounter();
	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow* targetWindow) override;
	void updateFPSUpdated(sf::Time elapsedTime);

private:
	sf::Time updateTime;
	sf::Text* statsText;
	int framesPassed = 0;
	sf::Time fpsTime = sf::Time::Zero;
	int frameCounter = 0;

	void updateFPS(sf::Time elapsedTime);

};

