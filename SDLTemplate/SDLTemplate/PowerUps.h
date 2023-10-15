#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include"SoundManager.h"
#include"bullet.h"
#include <vector>
#include"util.h"
#include "PlayerShip.h"
class PowerUps : public GameObject
{
public:
	~PowerUps();
	void start();
	void update();
	void draw();
	//can do inheritance here
	int getWidth();
	int getHeight();
	int getPositionX();
	int getPositionY();
	bool getIsThere();
	void doRemove();//check if shot
private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	//PlayerShip* playerTarget;
	int x;
	int y;
	float directionX;
	float directionY;
	int width;
	int height;
	int speed;
	float directionChangeTime;
	float currentDirectionChangeTime;
	bool isThere;
};

