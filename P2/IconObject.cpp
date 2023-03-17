#include "IconObject.h"
#include <iostream>
#include "BaseRunner.h"
#include "TextureManager.h"

IconObject::IconObject(String name, int textureIndex) : AGameObject(name)
{
	this->textureIndex = textureIndex;
}

void IconObject::initialize()
{
	//assign texture
	this->sprite = new sf::Sprite();
	//sf::Texture* texture = TextureManager::getInstance()->getStreamTextureFromList(this->textureIndex);
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(name,0);
	this->sprite->setTexture(*texture);
	this->sprite->setOrigin(this->sprite->getLocalBounds().width / 2, this->sprite->getLocalBounds().height / 2);

}

void IconObject::processInput(sf::Event event)
{
}

void IconObject::update(sf::Time deltaTime)
{
}
