#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class testRun
{

public:
	testRun();
	void run();
	float PlayerSpeed = 300.0f;
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;
	sf::RenderWindow mWindows;

private:
	void processEvents();
	void update();
	void render();
	void handlePlayerInput();


};

