#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "text.h"
#include<vector>
#include"Cat.h"
#include"Border.h"
#include"Food.h"
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
	
private:
	Cat* cat;
	Border* walls;
	Food* toy;

	std::vector<Food*> foodSpawned;
	std::vector<Cat*> bodyParts;

	void createBorder();
	void collisionsCheck();
	void deleteFood();
	//spawning code
	void foodSpawn();
	void despawnFood();

	void addTail();

	int spawnTimer;
	int currentTimer;

	int spawnTimer2;
	int currentTimer2;

	int objectSize;

	int currentPoints;
	int highScore;
};

