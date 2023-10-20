#include "Explosion.h"

Explosion::~Explosion()
{

}

void Explosion::start()
{
	//loading textures
	texture = loadTexture("gfx/explosion.png");
	width = 0;
	height = 0;
	currentSpawnTimer = 10;
	spawnTime = 10;
	//query
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Explosion::update()
{
	//despawn
	despawnExplosion();

}

void Explosion::draw()
{
	
	blit(texture, x, y);
	
}

void Explosion::getEnemyLocation(Enemy* mEnemyLocation)
{
	enemyLocation = mEnemyLocation;
}

void Explosion::getBossLocation(Boss* mBossLocation)
{
	bossLocation = mBossLocation;
}

void Explosion::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

int Explosion::getPositionX()
{
	return x;
}

int Explosion::getPositionY()
{
	return y;
}
void Explosion::despawnExplosion()
{

	if (currentSpawnTimer > 0)
		currentSpawnTimer--;
	if (currentSpawnTimer <= 0)
	{
	//check the ong spawned
		currentSpawnTimer = spawnTime;
		delete this;
	}
}
