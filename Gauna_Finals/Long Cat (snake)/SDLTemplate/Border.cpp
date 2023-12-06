#include "Border.h"

void Border::start()
{
	texture = loadTexture("gfx/border.png");
	width = 0;
	height = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Border::update()
{
}

void Border::draw()
{
	blit(texture, posX, posY);
}

void Border::setPos(int posX, int posY)
{
	this->posX = posX;
	this->posY = posY;
}

int Border::getPosX()
{
	return posX;
}

int Border::getPosY()
{
	return posY;
}

int Border::getWidth()
{
	return width;
}

int Border::getHeight()
{
	return height;
}
