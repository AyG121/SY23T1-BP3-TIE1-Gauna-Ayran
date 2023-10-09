#pragma once
#include "GameObject.h"
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include"SoundManager.h"
#include"bullet.h"
#include <vector>
#include"util.h"
#include "Enemy.h"
class Explosion : public GameObject
{
public:
	~Explosion();
	void start();
	void update();
	void draw();
	void despawnExplosion();
	//trying to spawn on enemy's position
	void getEnemyLocation(Enemy* mEnemyLocation);
	void setPosition(int xPos, int yPos);
	int getPositionX();
	int getPositionY();
private:
	SDL_Texture* texture;
	Enemy* enemyLocation;
	int x;
	int y;
	int width;
	int height;
	int	currentSpawnTimer;
	int spawnTime;
};


