#include "Boss.h"
#include"Scene.h"
Boss::Boss()
{
}
Boss::~Boss()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear();
}

void Boss::start()
{
	//loading textures
	texture = loadTexture("gfx/boss.png");
	directionX = -1;
	directionY = 0;
	//data initialization
	width = 0;
	height = 0;
	speed = 4;
	reloadTime = 15;
	currentReloadTime = 0;
	directionChangeTime = (rand() % 30) + 60;
	rngX = 0;
	rngY = 0;
	currentDirectionChangeTime = 0;
	currentChangeBullet = 0;
	this->isAlive = true;

	//query
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 20;
}

void Boss::update()
{
	//delete
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionY() > SCREEN_HEIGHT)
		{
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;
		}
	}
	
	//movement
	x += directionX * speed;
	y += directionY * speed;
	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;

	if (currentDirectionChangeTime == 0)
	{
		directionX = -directionX;
		currentDirectionChangeTime = directionChangeTime;
	}
	//gun system
	if (currentReloadTime > 0)
		currentReloadTime--;

	//changing bullets
	patternChange = 0;
	if (currentChangeBullet > 0)
		currentChangeBullet--;
	if (currentChangeBullet == 0)
	{
		patternChange = rand() % 2;
		currentChangeBullet = changeBullet;
	}
	if (currentReloadTime == 0)
	{
		if (patternChange == 0)
		{
			straightBulletPattern();
			//std::cout << "changed to straight bullet";
		}
		else
		{
			coneBulletPattern();
			//std::cout << "changed to cone bullet";

		}

	}


	if (this->y > SCREEN_HEIGHT)
	{
		delete this;
	}
}

void Boss::draw()
{
	if (this->isAlive)
	{
		blit(texture, x, y);
	}
}

void Boss::getPlayerTarget(PlayerShip* player)
{
	playerTarget = player;
}

void Boss::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

int Boss::getPositionX()
{
	return x;
}

int Boss::getPositionY()
{
	return y;
}

int Boss::getWidth()
{
	return width;
}

int Boss::getHeight()
{
	return height;
}

bool Boss::getIsAlive()
{
	return false;
}

void Boss::doDeath()
{
	this->isAlive = false;
}

void Boss::coneBulletPattern()
{
	float dx = -1;
	float dy = 0;

	calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);
	Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, dx, dy, 5, Side::ENEMY_SIDE);
	bullets.push_back(bullet);
	getScene()->addGameObject(bullet);
	SoundManager::playSound(sound);
	currentReloadTime = reloadTime;
}

void Boss::straightBulletPattern()
{
	float dx = -1;
	float dy = 0;
		calcSlope(rngX, rngY, x, y, &dx, &dy);
		Bullet* straightBullet = new Bullet(x + width, y - 2 + height / 2, dx, dy, 5, Side::ENEMY_SIDE);
		bullets.push_back(straightBullet);
		getScene()->addGameObject(straightBullet);
		currentReloadTime = reloadTime;
		SoundManager::playSound(sound);
		//update rng
		rngX = (rand() % 60) + 300;
		rngY = (rand() % 80) + 300;
}
