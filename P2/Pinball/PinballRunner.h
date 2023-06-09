
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
#include "../TextureDisplay.h"

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
    TextureDisplay* display = new TextureDisplay();

	//pinball vars

    bool enterPressed = false;
    sf::ContextSettings settings;


    std::list<Ball> balls;
    std::list<Ball>::iterator ballIt;

	bool g_bIsPlaying = false;
	bool g_bIsGameOver = false;
	int g_iScoreTotal = 0;
	int g_iBallsLeft = 420;
	int g_iHighestScore = 0;




    PinballTextureManager txtManager;



    sf::Color darkBlueCol = sf::Color(38, 70, 83);
    sf::Color cyanCol = sf::Color(42, 157, 143);
    sf::Color yellowCol = sf::Color(233, 196, 106);
    sf::Color orangeCol = sf::Color(244, 162, 97);
    sf::Color redCol = sf::Color(231, 69, 0);
    sf::Color pink = sf::Color(255, 192, 203);
    sf::Color blue = sf::Color(65, 105, 225);
    sf::Color yellow = sf::Color(255, 255, 102);



    Randomiser rand;
    std::list<Rect> rects;
    std::list<Rect>::iterator rectIt;

    std::list<OBB> obbs;
    std::list<OBB>::iterator obbIt;


    std::list<RoundBumper> roundBumpers;
    std::list<RoundBumper>::iterator roundBumperIt;

    std::list<RectangleBumper> rectangleBumpers;
    std::list<RectangleBumper>::iterator rectBumperIt;

    Rect topWall = Rect(Vector2D(50, -2), Vector2D(50, 3), darkBlueCol);
    Rect leftWall = Rect(Vector2D(0.5, 27.5), Vector2D(0.7, 30), darkBlueCol);

    Rect rightWall = Rect(Vector2D(95, 27.5), Vector2D(0.7, 30), darkBlueCol);
    Rect topRightCorner = Rect(Vector2D(94, 9.8), Vector2D(1, 1), darkBlueCol);
    Rect tunnel = Rect(Vector2D( 88.8, 37.2), Vector2D(0.2, 21), darkBlueCol);

    RoundBumper roundBumper1 = RoundBumper(Vector2D(63, 13), 2.2, 10, redCol);
    RoundBumper roundBumper2 = RoundBumper(Vector2D(10, 16), 2.2, 10, redCol);
    RoundBumper largeRoundBumper = RoundBumper(Vector2D(40,18), 2.7, 10, blue);
    RoundBumper largeRoundBumper2 = RoundBumper(Vector2D(55, 27), 2.7, 10, redCol);
    RoundBumper largeRoundBumper3 = RoundBumper(Vector2D(28, 10), 2.7, 10, yellow);

    Paddle leftPaddle = Paddle(Vector2D(29.6, 46.5), Vector2D(10, 1.5), 0.5, true, blue);
    Paddle rightPaddle = Paddle(Vector2D(57.6, 46.5), Vector2D(10,1.5), 0.5, false, yellow);

    //end of ramps
    Rect bottomLeftCorner = Rect(Vector2D(1.3, 25), Vector2D(2, 2), darkBlueCol);
    Rect bottomRightCorner = Rect(Vector2D(87, 25), Vector2D(2, 2), darkBlueCol);

    //ramps
    OBB leftRamp = OBB(Vector2D(12.6, 34), Vector2D(16, 1.8), 0.6, darkBlueCol);
    OBB rightRamp = OBB(Vector2D(74.6, 34), Vector2D(16, 1.8), -0.6, darkBlueCol);


    //middle rec bumpers
    RectangleBumper rectBumper1 = RectangleBumper(Vector2D(20, 25), Vector2D(0.8, 4), 0.3, 20, darkBlueCol);
    RectangleBumper rectBumper2 = RectangleBumper(Vector2D(50, 13), Vector2D(0.8, 4), -0.3, 20, darkBlueCol);

    sf::Font arcadeFont;
    //arcadeFont.loadFromFile("resources\\BebasNeue Regular.otf");

    sf::Text highestScoreText = sf::Text("Top Score: " + std::to_string(g_iHighestScore), arcadeFont, 60);
    

    sf::Text scoreText = sf::Text("Score: " + std::to_string(g_iScoreTotal), arcadeFont, 60);

    sf::Text ballsLeftText = sf::Text("Balls: " + std::to_string(g_iBallsLeft), arcadeFont, 60);

    sf::Text gameOverText = sf::Text("GAME OVER", arcadeFont, 150);
    sf::Text Continue = sf::Text("PRESS ENTER TO CONTINUE", arcadeFont, 100);
    sf::Text Numkeys = sf::Text("PRESS NUMKEYS 1-8", arcadeFont, 150);



};



