#include "Enemy.h"
#include"Scene.h"
Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear();
}

void Enemy::start()
{
	//loading textures
	texture = loadTexture("gfx/enemy.png");
	directionX = -1;
	directionY = 1;
	//data initialization
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 60;
	currentReloadTime = 0;
	directionChangeTime = (rand() % 10) + 50;
	currentDirectionChangeTime = 0;
	this->isAlive = true;
	
	//query
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 64;
}

void Enemy::update()
{
	//delete
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() < 0)
		{
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;
		}
	}

	x += directionX * speed;
	y += directionY * speed;

	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;

	if (currentDirectionChangeTime == 0)
	{
		directionX = -directionX;
		currentDirectionChangeTime = directionChangeTime;
	}

	if (currentReloadTime > 0)
		currentReloadTime--;
	//fire sound
	if (currentReloadTime == 0)
	{
		float dx=-1;
		float dy = 0;

		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(),x,y,&dx,&dy);

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, dx, dy, 10, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		currentReloadTime = reloadTime;
	}

	if (this->x < 0)
	{
		delete this;
	}

}

void Enemy::draw()
{
	if (this->isAlive)
	{
		blit(texture, x, y);
	}
}

void Enemy::getPlayerTarget(PlayerShip* player)
{
	playerTarget = player;
}

void Enemy::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

int Enemy::getPositionX()
{
	return x;
}

int Enemy::getPositionY()
{
	return y;
}

int Enemy::getWidth()
{
	return width;
}

int Enemy::getHeight()
{
	return height;
}

bool Enemy::getIsAlive()
{
	return isAlive;
}

void Enemy::doDeath()
{
	this->isAlive = false;
}

