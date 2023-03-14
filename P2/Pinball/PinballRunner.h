
#include <SFML/Graphics.hpp>
#include <vector>


#include <SFML/Graphics.hpp>
#include "Randomiser.h"
#include "config.h"
#include "Vector2D.h"
#include "ball.h"
#include "rect.h"
#include "obb.h"
#include "manifold.h"
#include "PinballTextureManager.h"
#include <list>
#include "../FPSCounter.h"

#include "paddle.h"
#include "roundBumper.h"
#include "rectangleBumper.h"


using namespace std;
class PinballRunner : private sf::NonCopyable
{
public:
	static const sf::Time	TIME_PER_FRAME;
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;

	PinballRunner();
	void run();

private:

	sf::RenderWindow		window;

	void render();
	void processEvents();
	void update(sf::Time elapsedTime);
	void physicsUpdate(sf::Time elapsedTime);
    FPSCounter* fpsCounter = new FPSCounter();


	//pinball vars
    sf::ContextSettings settings;


    std::list<Ball> balls;
    std::list<Ball>::iterator ballIt;

	bool g_bIsPlaying = false;
	bool g_bIsGameOver = false;
	int g_iScoreTotal = 0;
	int g_iBallsLeft = 3;
	int g_iHighestScore = 0;

	void loseLife();


    PinballTextureManager txtManager;

	sf::Sprite background;


    sf::Color darkBlueCol = sf::Color(38, 70, 83);
    sf::Color cyanCol = sf::Color(42, 157, 143);
    sf::Color yellowCol = sf::Color(233, 196, 106);
    sf::Color orangeCol = sf::Color(244, 162, 97);
    sf::Color redCol = sf::Color(231, 111, 81);



    Randomiser rand;
    std::list<Rect> rects;
    std::list<Rect>::iterator rectIt;

    std::list<OBB> obbs;
    std::list<OBB>::iterator obbIt;


    std::list<RoundBumper> roundBumpers;
    std::list<RoundBumper>::iterator roundBumperIt;

    std::list<RectangleBumper> rectangleBumpers;
    std::list<RectangleBumper>::iterator rectBumperIt;

    Rect topWall = Rect(Vector2D(18, 8.8), Vector2D(17, 0.7), darkBlueCol);
    Rect leftWall = Rect(Vector2D(0.5, 27.5), Vector2D(0.7, 30), darkBlueCol);

    Rect rightWall = Rect(Vector2D(35.5, 27.5), Vector2D(0.7, 30), darkBlueCol);
    Rect topRightCorner = Rect(Vector2D(34.8, 9.8), Vector2D(0.5, 0.5), darkBlueCol);
    Rect tunnel = Rect(Vector2D(32.9, 34), Vector2D(0.2, 21), darkBlueCol);

    RoundBumper roundBumper1 = RoundBumper(Vector2D(10, 13), 1.7, 10, cyanCol);
    RoundBumper roundBumper2 = RoundBumper(Vector2D(27, 16), 1.7, 10, yellowCol);
    RoundBumper largeRoundBumper = RoundBumper(Vector2D(17.5, 21), 2, 10, orangeCol);
    RoundBumper largeRoundBumper2 = RoundBumper(Vector2D(6, 25), 2, 10, yellowCol);
    RoundBumper largeRoundBumper3 = RoundBumper(Vector2D(28, 25), 2, 10, cyanCol);

    Paddle leftPaddle = Paddle(Vector2D(10, 44.5), Vector2D(5, 0.8), 0.5, true, cyanCol);
    Paddle rightPaddle = Paddle(Vector2D(23, 44.5), Vector2D(5, 0.8), 0.5, false, cyanCol);

    Rect bottomLeftCorner = Rect(Vector2D(1.3, 37.5), Vector2D(0.5, 0.5), darkBlueCol);
    Rect bottomRightCorner = Rect(Vector2D(32.5, 37.5), Vector2D(0.5, 0.5), darkBlueCol);

    OBB leftRamp = OBB(Vector2D(5.5, 40.5), Vector2D(6, 0.5), 0.6, darkBlueCol);
    OBB rightRamp = OBB(Vector2D(27.7, 40.5), Vector2D(6, 0.5), -0.6, darkBlueCol);

    RectangleBumper rectBumper1 = RectangleBumper(Vector2D(4.5, 33), Vector2D(0.5, 2), 0.3, 20, darkBlueCol);
    RectangleBumper rectBumper2 = RectangleBumper(Vector2D(30, 33), Vector2D(0.5, 2), -0.3, 20, darkBlueCol);

    sf::Font arcadeFont;
    //arcadeFont.loadFromFile("resources\\BebasNeue Regular.otf");

    sf::Text highestScoreText = sf::Text("Top Score: " + std::to_string(g_iHighestScore), arcadeFont, 60);
    

    sf::Text scoreText = sf::Text("Score: " + std::to_string(g_iScoreTotal), arcadeFont, 60);

    sf::Text ballsLeftText = sf::Text("Balls: " + std::to_string(g_iBallsLeft), arcadeFont, 60);

    sf::Text gameOverText = sf::Text("GAME OVER", arcadeFont, 150);



};



