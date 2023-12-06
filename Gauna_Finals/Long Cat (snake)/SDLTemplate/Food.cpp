#include "Food.h"

void Food::start()
{
	texture = loadTexture("gfx/yarn.png");

	width = 0;
	height = 0;

	this->isThere = true;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

}

void Food::update()
{
	if (!this->isThere)
	{
		delete this;
	}
}

void Food::draw()
{
	if (this->isThere)
	{
		blit(texture, posX, posY);
	}
}

int Food::getWidth()
{
	return width;
}

int Food::getHeight()
{
	return height;
}

int Food::getPosX()
{
	return posX;
}

int Food::getPosY()
{
	return posY;
}

void Food::setPos(int posX, int posY)
{
	this->posX = posX;
	this->posY = posY;
}

bool Food::getIsThere()
{
	return isThere;
}

void Food::doRemove()
{
	this->isThere = false;
}
