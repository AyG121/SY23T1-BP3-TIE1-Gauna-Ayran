#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
class Food : public GameObject
{
public:
	void start();
	void update();
	void draw();

	int getWidth();
	int getHeight();
	int getPosX();
	int getPosY();

	void setPos(int posX, int posY);
	bool getIsThere();
	void doRemove();//check if eaten
private:
	SDL_Texture* texture;
	int posX;
	int posY;

	int width;
	int height;
	int speed;

	bool isThere;
};

