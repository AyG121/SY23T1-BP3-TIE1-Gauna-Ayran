#include "PowerUps.h"

PowerUps::~PowerUps()
{
	
}

void PowerUps::start()
{
	//loading textures
	texture = loadTexture("gfx/points.png");
	directionX = -1;
	directionY = 1;
	//data initialization
	width = 0;
	height = 0;
	speed = 2;
	directionChangeTime = (rand() % 35) + 80;
	currentDirectionChangeTime = 0;
	this->isThere = true;
	//query
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void PowerUps::update()
{
	x += directionX * speed;
	y += directionY * speed;

	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;

	if (currentDirectionChangeTime == 0)
	{
		directionX = -directionX;
		currentDirectionChangeTime = directionChangeTime;
	}
	if (!this->isThere)
	{
		delete this;
	}
}

void PowerUps::draw()
{
	if (this->isThere)
	{
		blit(texture, x, y);
	}
}


int PowerUps::getWidth()
{
	return width;
}

int PowerUps::getHeight()
{
	return height;
}

int PowerUps::getPositionX()
{
	return x;
}

int PowerUps::getPositionY()
{
	return y;
}

void PowerUps::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

bool PowerUps::getIsThere()
{
	return isThere;
}

void PowerUps::doRemove()
{
	this->isThere = false;
}
