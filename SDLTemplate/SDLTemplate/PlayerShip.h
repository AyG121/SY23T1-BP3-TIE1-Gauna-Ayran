#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include"SoundManager.h"
#include"bullet.h"
#include <vector>
class PlayerShip:public GameObject
{
public:
	~PlayerShip();
	void start();
	void update();
	void draw();
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
	int x;
	int y;
	int width;
	int height;
	int speed;
	int accelerate;
	int slowDown;
	float reloadTime;
	float currentReloadTime;
	float secondReloadTime;
	std::vector<Bullet*>bullets;
	bool isAlive;
};

