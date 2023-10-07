#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include"SoundManager.h"
#include"bullet.h"
#include <vector>
#include"util.h"
#include "PlayerShip.h"
class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();
	void start();
	void update();
	void draw();
	void getPlayerTarget(PlayerShip* player);
	void setPosition(int xPos, int yPos);
	//can do inheritance here
	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();
	bool getIsAlive();
	void doDeath();
private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	PlayerShip* playerTarget;
	int x;
	int y;
	float directionX;
	float directionY;
	int width;
	int height;
	int speed;
	int accelerate;
	int slowDown;
	float reloadTime;
	float currentReloadTime;
	float secondReloadTime;
	float directionChangeTime;
	float currentDirectionChangeTime;
	std::vector<Bullet*>bullets;
	bool isAlive;
};

