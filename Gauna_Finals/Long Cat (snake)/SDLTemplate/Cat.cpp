#include "Cat.h"

void Cat::start()
{
	//load texture
	head = loadTexture("gfx/head.png");
	body = loadTexture("gfx/body.png");
	//initialize
	width = 0;
	height = 0;

	speed = 32;
	isAlive = true;

	tailNumber = 0;
	
	points = 0;
	timer = 5;
	currentTimer = 0;
	direction = Direction::East;

	CatBody headPart;
	headPart.x = SCREEN_WIDTH / 2;
	headPart.y = SCREEN_HEIGHT / 2;

	bodyParts.push_back(headPart);

	//query
	SDL_QueryTexture(head, NULL, NULL, &width, &height);
	SDL_QueryTexture(body, NULL, NULL, &width, &height);
}

void Cat::update()
{
	if (app.keyboard[SDL_SCANCODE_W] && direction != Direction::South && currentTimer == 1)
	{
		direction = Direction::North;
	}
	if (app.keyboard[SDL_SCANCODE_A] && direction != Direction::East && currentTimer == 1)
	{
		direction = Direction::West;
	}
	if (app.keyboard[SDL_SCANCODE_S] && direction != Direction::North && currentTimer == 1)
	{
		direction = Direction::South;
	}
	if (app.keyboard[SDL_SCANCODE_D] && direction != Direction::West && currentTimer == 1)
	{
		direction = Direction::East;
	}

	if (currentTimer == 1)
	{
		bodyParts[0].prevY = bodyParts[0].y;
		bodyParts[0].prevX = bodyParts[0].x;
	}

	if (direction == Direction::North && currentTimer == 1)
	{
		headDirection = 270;
		bodyParts[0].prevY = bodyParts[0].y;
		bodyParts[0].y -= speed;
	}
	if (direction == Direction::South && currentTimer == 1)
	{
		headDirection = 90;
		bodyParts[0].prevY = bodyParts[0].y;
	
		bodyParts[0].y += speed;
	}
	if (direction == Direction::West && currentTimer == 1)
	{
		headDirection = 180;
		bodyParts[0].prevX = bodyParts[0].x;
		bodyParts[0].x -= speed;
	}
	if (direction == Direction::East && currentTimer == 1)
	{
		headDirection = 0;
		bodyParts[0].prevX = bodyParts[0].x;
		bodyParts[0].x += speed;

	}

	if (currentTimer > 0)
	{
		currentTimer--;
	}

	if (currentTimer <= 0)
	{
		currentTimer = timer;

		//holds head position
		int headPosX = bodyParts[0].x;
		int headPosY = bodyParts[0].y;

		for (int i = 1; i < bodyParts.size(); i++)
		{
			bodyParts[i].prevY = bodyParts[i].y;
			bodyParts[i].prevX = bodyParts[i].x;

			bodyParts[i].x = bodyParts[i - 1].prevX;
			bodyParts[i].y = bodyParts[i - 1].prevY;
		}
		catEatSelf();
	}
	if (isAlive == false)
	{
		if (app.keyboard[SDL_SCANCODE_SPACE])
		{
			bodyParts.clear();
			start();
			isAlive = true;
		}
	}
}

void Cat::draw()
{
	if (isAlive)
	{
		for (int i = 0; i < bodyParts.size(); i++)
		{
			if (i == 0)
			{
				blitRotate(head, bodyParts[i].x, bodyParts[i].y, headDirection);
			}
			else
			{
				blitRotate(body, bodyParts[i].x , bodyParts[i].y,headDirection);
			}
		}
	}
}

void Cat::addBodyPart()
{
	CatBody newPart;
	//where new part spawns
	newPart.x = bodyParts[bodyParts.size() - 1].prevX;
	newPart.y = bodyParts[bodyParts.size() - 1].prevY;
	bodyParts.push_back(newPart);
	

	tailNumber++;
}

int Cat::getBodyX(int i)
{
	return bodyParts[i].x;
}

int Cat::getBodyY(int i)
{
	return bodyParts[i].y;
}

void Cat::setBodyX(int i)
{
	this->bodyParts[i].x = i;;
}

void Cat::setBodyY(int i)
{
	this->bodyParts[i].y = i;;
}

int Cat::getTailNumber()
{
	return tailNumber;
}

void Cat::setTailNumber(int tailNumber)
{
	this->tailNumber = tailNumber;
}


int Cat::getWidth()
{
	return width;
}

int Cat::getHeight()
{
	return height;
}

int Cat::getSpeed()
{
	return speed;
}

Direction Cat::getDirection()
{
	return Direction();
}

void Cat::setDirection(Direction direction)
{
	this->direction = direction;
}

bool Cat::getIsAlive()
{
	return isAlive;
}

void Cat::doDeath()
{
	isAlive = false;
	
}

int Cat::getPoints()
{
	return points;
}

void Cat::setPoints(int i)
{
	this->points = i;
}

void Cat::catEatSelf()
{
	for (int i = 2; i < bodyParts.size(); i++)
	{
		if (bodyParts[0].x == bodyParts[i].x && bodyParts[0].y == bodyParts[i].y) 
		{
			doDeath();
		}
	}
}
