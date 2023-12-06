#pragma once
#include "GameObject.h"
#include <vector>
#include "common.h"
#include "draw.h"
#include"util.h"
#include <string>
enum class Direction
{
	North,
	South,
	East,
	West,
	Stop
};
struct CatBody
{
	int x;
	int y;
	int prevX;
	int prevY;
};
class Cat:public GameObject
{
public:

	 void start();
	 void update();
	 void draw();

	 void addBodyPart();
	 int getBodyX(int i);
	 int getBodyY(int i);

	 void setBodyX(int i);
	 void setBodyY(int i);

	 int getTailNumber();
	 void setTailNumber(int tailNumber);

	 int getWidth();
	 int getHeight();
	 int getSpeed();

	 Direction getDirection();
	 void setDirection(Direction direction);

	 bool getIsAlive();
	 void doDeath();

	 int getPoints();
	 void setPoints(int i);
	 void catEatSelf();
private:

	SDL_Texture* head;
	SDL_Texture* body;

	Direction direction;
	std::vector<CatBody> bodyParts;
	int posX;
	int posY;
	int width;
	int height;
	int speed;

	int timer;
	int currentTimer;

	bool isAlive;

	int tailNumber;
	int headDirection;

	int points;
};

