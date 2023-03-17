#include "TextureDisplay.h"
#include <iostream>

#include "AudioManager.h"
#include "TextureManager.h"
#include "Pinball/PinballRunner.h"
#include "GameObjectManager.h"
#include "IconObject.h"

TextureDisplay::TextureDisplay() : AGameObject("TextureDisplay")
{

}

void TextureDisplay::initialize()
{

}

void TextureDisplay::processInput(sf::Event event)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		if (!onePressed)
		{
			sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("daimon", 0);
			changeDisplay("daimon");
			playSound("daimon");
			onePressed = true;
		}
	}
	else
	{
		onePressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		if (!twoPressed)
		{
			changeDisplay("cyberpunk");
			playSound("cyberpunk");
			twoPressed = true;
		}
	}
	else
	{
		twoPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		if (!threePressed)
		{
			changeDisplay("farcry");
			playSound("farcry");
			threePressed = true;
		}
	}
	else
	{
		threePressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		if (!fourPressed)
		{
			changeDisplay("fonv");
			playSound("fonv");
			fourPressed = true;
		}
	}
	else
	{
		fourPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		if (!fivePressed)
		{
			changeDisplay("majula");
			playSound("majula");
			fivePressed = true;
		}
	}
	else
	{
		fivePressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
		if (!sixPressed)
		{
			changeDisplay("malenia");
			playSound("malenia");
			sixPressed = true;
		}
	}
	else
	{
		sixPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
	{
		if (!sevenPressed)
		{
			changeDisplay("skyrim");
			playSound("skyrim");
			sevenPressed = true;
		}
	}
	else
	{
		sevenPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
	{
		if (!eightPressed)
		{
			changeDisplay("witcher");
			playSound("witcher");
			eightPressed = true;

		}
	}
	else
	{
		eightPressed = false;
	}
}

void TextureDisplay::update(sf::Time deltaTime)
{
	
	this->ticks += PinballRunner::TIME_PER_FRAME.asMilliseconds();
	
	if (this->streamingType == StreamingType::SINGLE_STREAM && this->ticks > this->STREAMING_LOAD_DELAY && (finishedLoadingAudio == false || finishedLoadingImage == false))
	{

		this->ticks = 0.0f;
		TextureManager::getInstance()->loadSingleStreamAsset(this->numDisplayed, this);
		AudioManager::getInstance()->LoadAudio(numDisplayed, this);

		//spawnObject();

		this->numDisplayed++;
	}

	//<code here for spawning icon object periodically>
}

void TextureDisplay::onFinishedExecution(String assetName)
{

	ImageAssetsLoaded++;
	if (ImageAssetsLoaded == TextureManager::getInstance()->streamingAssetCount)
	{
		finishedLoadingImage = true;
		std::cout << "fiinish images" << std::endl;

	}
	IconObject* iconObj = new IconObject(assetName, 0);
	iconObj->setActive(false);
	this->iconList.push_back(iconObj);
	//std::cout << iconList.size() << std::endl;

	//set position
	iconObj->setPosition(1920 / 2, 1080 / 2);


	GameObjectManager::getInstance()->addObject(iconObj);
	//std::cout << TextureManager::getInstance()->streamingAssetCount << std::endl;
}

void TextureDisplay::onFinishedExecutionSound()
{

	AudioAssetsLoaded++;
	if (AudioAssetsLoaded == AudioManager::getInstance()->totalAssets)
	{
		std::cout << "finish audio" << std::endl;
		finishedLoadingAudio = true;

		/*for (std::vector<sf::Sound*>::iterator it = AudioManager::getInstance()->soundList.begin(); it != AudioManager::getInstance()->soundList.end(); ++it) {
			(*it)->setVolume(20);
		}*/

	}
	
}



bool TextureDisplay::checkLoading()
{
	if (finishedLoadingImage && finishedLoadingAudio)
	{
		finishedLoadingAll = true;
	}
	return finishedLoadingAll;
}

void TextureDisplay::spawnObject()
{
	String objectName = "Icon_" + to_string(this->iconList.size());
	IconObject* iconObj = new IconObject(objectName, this->iconList.size());
	this->iconList.push_back(iconObj);
	//

	//set position
	int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
	float x = this->columnGrid * IMG_WIDTH;
	float y = this->rowGrid * IMG_HEIGHT;
	iconObj->setPosition(x, y);

	//std::cout << "Set position: " << x << " " << y << std::endl;

	this->columnGrid++;
	if (this->columnGrid == this->MAX_COLUMN)
	{
		this->columnGrid = 0;
		this->rowGrid++;
	}
	GameObjectManager::getInstance()->addObject(iconObj);
}

void TextureDisplay::changeDisplay(String assetName)
{
	IconObject* iconObj = new IconObject(assetName, iconList.size());

	if (!iconList.empty())
	{
		for (IconList::iterator iconObjIt = iconList.begin(); iconObjIt != iconList.end(); ++iconObjIt)
		{
			if ((*iconObjIt)->getName() == iconObj->getName())
			{
				for (IconList::iterator iconObjIts = iconList.begin(); iconObjIts != iconList.end(); ++iconObjIts)
				{
					(*iconObjIts)->setActive(false);
				}
				//std::cout << (*iconObjIt)->getName() << " VS " << iconObj->getName() << std::endl;

				(*iconObjIt)->setActive(true); 
				//std::cout << "image exists already" << std::endl;
				return;
			}
		}
	}
}

void TextureDisplay::playSound(String assetName)
{
	for (std::vector<sf::Sound*>::iterator it = AudioManager::getInstance()->soundList.begin(); it != AudioManager::getInstance()->soundList.end(); ++it) {
		if ((*it)->getStatus() == sf::SoundSource::Playing)
		{
			(*it)->stop();
		}
	}
	//AudioManager::getInstance()->soundList[key-1]->play();
	AudioManager::getInstance()->soundMap[assetName][0]->play();

}
