#include "Bullet.h"
#include "draw.h"
Bullet::Bullet(int positionX, int positionY, float directionX, float directionY, float speed, Side side)
{
	this->x = positionX;
	this->y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
	this->side = side;
}
void Bullet::start()
{
	width = 0;
	height = 0;
	if (side == Side::PLAYER_SIDE)
	{
		texture = loadTexture("gfx/playerBullet.png");
	}
	else if (side == Side::ENEMY_SIDE)
	{
		texture = loadTexture("gfx/alienBullet.png");
	}
	else
	{
		texture = loadTexture("gfx/bossBullet.png");
	}

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Bullet::update()
{
	x += directionX *speed;
	y += directionY * speed;
}

void Bullet::draw()
{
	blit(texture, x, y);
}

int Bullet::getPositionX()
{
	return x;
}

int Bullet::getPositionY()
{
	return y;
}

int Bullet::getWidth()
{
	return width;
}

int Bullet::getHeight()
{
	return height;
}

Side Bullet::getSide()
{
	return side;
}
