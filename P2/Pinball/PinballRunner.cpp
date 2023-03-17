#include "PinballRunner.h"
#include "../GameObjectManager.h"
#include "../BGObject.h"
#include "../TextureManager.h"



const sf::Time PinballRunner::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

PinballRunner::PinballRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "P2", sf::Style::Close) {
	//load initial textures
	TextureManager::getInstance()->loadFromAssetList();

	//load objects
	BGObject* bgObject = new BGObject("BGObject");
	//GameObjectManager::getInstance()->addObject(bgObject);

	GameObjectManager::getInstance()->addObject(display);
	GameObjectManager::getInstance()->addObject(fpsCounter);


    //pinball -------------------------------------------
    //settings.antialiasingLevel = 8;



    
    //arcadeFont.loadFromFile("resources\\BebasNeue Regular.otf");
    arcadeFont.loadFromFile("Media/Sansation.ttf");
    Continue.setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
    Continue.setOutlineThickness(2.5f);
    Numkeys.setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
    Numkeys.setOutlineThickness(2.5f);

    highestScoreText.setFillColor(redCol);
    highestScoreText.setPosition(40, 5);

    scoreText.setFillColor(redCol);
    scoreText.setPosition(40, 80);

    ballsLeftText.setFillColor(redCol);
    ballsLeftText.setPosition(500, 5);

    gameOverText.setFillColor(sf::Color::Black);
    gameOverText.setPosition(100, 400);

	Continue.setFillColor(sf::Color::White);
    Continue.setPosition(300, 400);

    Numkeys.setFillColor(sf::Color::White);
    Numkeys.setPosition(300, 400);

    
     rectangleBumpers.push_back(rectBumper1);
    rectangleBumpers.push_back(rectBumper2);

   roundBumpers.push_back(roundBumper1);
    roundBumpers.push_back(roundBumper2);
    roundBumpers.push_back(largeRoundBumper);
    roundBumpers.push_back(largeRoundBumper2);
    roundBumpers.push_back(largeRoundBumper3);


    rects.push_back(topWall);
    rects.push_back(leftWall);
    rects.push_back(rightWall);
    rects.push_back(tunnel);
    rects.push_back(topRightCorner);

    rects.push_back(bottomLeftCorner);
    rects.push_back(bottomRightCorner);

    obbs.push_back(rightRamp);
    obbs.push_back(leftRamp);



}

void PinballRunner::run() {
	sf::Clock clock;
	window.setFramerateLimit(60);

	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (this->window.isOpen())
	{
        sf::Event event;
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
        
		while (timeSinceLastUpdate >= TIME_PER_FRAME)
		{

			timeSinceLastUpdate -= TIME_PER_FRAME;

            /*if (window.pollEvent(event) && !display->checkLoading())
            {

            	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                    if (!g_bIsGameOver) {
                        Vector2D pos = Vector2D(90, 55);
                        Vector2D vel = Vector2D(0, -70);
                        Vector2D acc = Vector2D(0, 20);

                        Ball ball = Ball(pos, vel, acc, 3);
                        ball.setColour(sf::Color::Black);
                        balls.push_back(ball);
                        g_bIsPlaying = true;
                    }
                }

            }*/
            if (!display->checkLoading())
            {
	            if (this->window.pollEvent(event)) {
	                switch (event.type) {
	                case sf::Event::Closed:
	                    this->window.close();
	                    break;
	                case sf::Event::KeyPressed:
	                    switch (event.key.code)
	                    {
	                    case sf::Keyboard::Space:
	                        if (!g_bIsGameOver) {
	                            Vector2D pos = Vector2D(90, 55);
	                            Vector2D vel = Vector2D(0, -70);
	                            Vector2D acc = Vector2D(0, 20);

	                            Ball ball = Ball(pos, vel, acc, 2.5);
	                            ball.setColour(sf::Color::Black);
	                            balls.push_back(ball);
	                            g_bIsPlaying = true;
	                        }
	                        break;
						case sf::Keyboard::Left:
	                        std::cout << "we clicking" << std::endl;
	                        leftPaddle.flip("up");
	                        // Handle A key press
	                        break;
	                    case sf::Keyboard::Right:
	                        rightPaddle.flip("up");
	                        // Handle D key press
	                        break;
	                    }
	                    break;
	                case sf::Event::KeyReleased:
	                    switch (event.key.code)
	                    {
	                    case sf::Keyboard::Left:
	                        leftPaddle.flip("down");
	                        std::cout << "we out" << std::endl;
	                        // Handle A key press
	                        break;
	                    case sf::Keyboard::Right:
	                        rightPaddle.flip("down");
	                        // Handle D key press
	                        break;
	                    }
	                    break;
	                }
	            }
            }
            else
            	processEvents();

            update(elapsedTime);

        }
        physicsUpdate(elapsedTime);
        render();

        fpsCounter->updateFPSUpdated(elapsedTime);

	}
}

void PinballRunner::processEvents()
{
	sf::Event event;
    if (this->window.pollEvent(event)) {
        switch (event.type) {

        default: GameObjectManager::getInstance()->processInput(event);
            break;
        case sf::Event::Closed:
            this->window.close();
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::Enter:
                std::cout << "pressed space" << std::endl;
                enterPressed = true;
                break;
            }
        }
    }



   

}

void PinballRunner::update(sf::Time elapsedTime) {

	GameObjectManager::getInstance()->update(elapsedTime);

	if (display->checkLoading())
    {
        

       // scoreText.setString("Score: " + std::to_string(g_iScoreTotal));
       // ballsLeftText.setString("Balls: " + std::to_string(g_iBallsLeft));
       // highestScoreText.setString("Top score: " + std::to_string(g_iHighestScore));

       // //printf("Score: %i ", iScoreTotal);
       // //printf("Lives: %i \n", iBallsLeft);

       // loseLife();

       // if (g_iBallsLeft <= 0) {
       //     g_bIsGameOver = true;
       //     //clock.restart();
       // }

       // //
       // if (g_iScoreTotal > g_iHighestScore) {
       //     g_iHighestScore = g_iScoreTotal;
       // }
       // scoreText.setString("Score: " + std::to_string(g_iScoreTotal));
       // ballsLeftText.setString("Balls: " + std::to_string(g_iBallsLeft));
       // highestScoreText.setString("Top score: " + std::to_string(g_iHighestScore));


       ///* if (g_bIsGameOver) {
       //     g_bIsPlaying = false;

       //     window.draw(gameOverText);
       //     g_iScoreTotal = 0;
       //     g_iBallsLeft = 420;

       //     g_bIsGameOver = false;
       // }*/
    }
}

void PinballRunner::physicsUpdate(sf::Time elapsedTime)
{
    if (!g_bIsGameOver && !display->checkLoading() || !enterPressed)
    {
        //std::cout << "updating" << std::endl;
        const float fSeconds = elapsedTime.asSeconds();

        for (ballIt = balls.begin(); ballIt != balls.end(); ++ballIt) {

            for (auto p = balls.begin(); p != balls.end(); ++p) {

                if (ballIt != p) {
                    Manifold m = Manifold(&ballIt->body, &p->body);
                    if (m.CircleVsCircle()) {
                        m.correctPosition();
                        m.applyRotationalImpulse();
                    }
                }
            }

            for (roundBumperIt = roundBumpers.begin(); roundBumperIt != roundBumpers.end(); ++roundBumperIt) {

                Manifold m = Manifold(&roundBumperIt->body, &ballIt->body);
                if (m.CircleVsCircle()) {
                    g_iScoreTotal += roundBumperIt->getPoints();
                    m.correctPosition();
                    m.applyRotationalImpulse();
                }
            }

            for (rectBumperIt = rectangleBumpers.begin(); rectBumperIt != rectangleBumpers.end(); ++rectBumperIt) {

                Manifold m = Manifold(&rectBumperIt->body, &ballIt->body);
                if (m.CircleVsOBB()) {
                    g_iScoreTotal += rectBumperIt->getPoints();
                    m.correctPosition();
                    m.applyRotationalImpulse();
                }
            }

            for (rectIt = rects.begin(); rectIt != rects.end(); ++rectIt) {

                Manifold m = Manifold(&rectIt->body, &ballIt->body);
                if (m.CircleVsRect()) {
                    m.correctPosition();
                    m.applyRotationalImpulse();
                }
            }

            for (obbIt = obbs.begin(); obbIt != obbs.end(); ++obbIt) {
                Manifold m = Manifold(&obbIt->body, &ballIt->body);
                if (m.CircleVsOBB()) {
                    m.correctPosition();
                    m.applyRotationalImpulse();
                }
            }

            Manifold leftPaddleManifold = Manifold(&rightPaddle.body, &ballIt->body);
            if (leftPaddleManifold.CircleVsOBB()) {
                leftPaddleManifold.correctPosition();
                leftPaddleManifold.applyRotationalImpulse();
            }

            Manifold rightPaddleManifold = Manifold(&leftPaddle.body, &ballIt->body);
            if (rightPaddleManifold.CircleVsOBB()) {
                rightPaddleManifold.correctPosition();
                rightPaddleManifold.applyRotationalImpulse();
            }

            ballIt->body.update(fSeconds);


        }

        for (roundBumperIt = roundBumpers.begin(); roundBumperIt != roundBumpers.end(); ++roundBumperIt) {
            roundBumperIt->body.update(fSeconds);
        }

        for (rectBumperIt = rectangleBumpers.begin(); rectBumperIt != rectangleBumpers.end(); ++rectBumperIt) {
            rectBumperIt->body.update(fSeconds);
        }

        for (rectIt = rects.begin(); rectIt != rects.end(); ++rectIt) {
            rectIt->body.update(fSeconds);
        }

        for (obbIt = obbs.begin(); obbIt != obbs.end(); ++obbIt) {
            obbIt->body.update(fSeconds);
        }

        rightPaddle.body.update(fSeconds);
        rightPaddle.clampPaddle();

        leftPaddle.body.update(fSeconds);
        leftPaddle.clampPaddle();

        //clock.restart();
    }
}


void PinballRunner::render() {
	this->window.clear(pink);

	if (!display->checkLoading() || !enterPressed)
	{
        

        for (rectIt = rects.begin(); rectIt != rects.end(); ++rectIt)
        {
            window.draw(*rectIt);

        }

        for (obbIt = obbs.begin(); obbIt != obbs.end(); ++obbIt)
        {
            window.draw(*obbIt);
        }

        for (ballIt = balls.begin(); ballIt != balls.end(); ++ballIt)
        {
            window.draw(*ballIt);
        }

        for (roundBumperIt = roundBumpers.begin(); roundBumperIt != roundBumpers.end(); ++roundBumperIt)
        {
            window.draw(*roundBumperIt);
        }

        for (rectBumperIt = rectangleBumpers.begin(); rectBumperIt != rectangleBumpers.end(); ++rectBumperIt)
        {
            window.draw(*rectBumperIt);
        }

        window.draw(rightPaddle);
        window.draw(leftPaddle);
        if (display->checkLoading())
            window.draw(Continue);
	}
    

    GameObjectManager::getInstance()->draw(&this->window);


    if (enterPressed)
    {
        window.draw(Numkeys);

    }
   /* window.draw(highestScoreText);
    window.draw(scoreText);
    window.draw(ballsLeftText);*/

	this->window.display();
}
