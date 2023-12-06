#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	//player
	cat = new Cat();
	this->addGameObject(cat);
	highScore = 0;
}

GameScene::~GameScene()
{
	delete cat;
	delete walls;
	delete toy;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here
	initFonts();
	//tail delay
	spawnTimer = 5;
	currentTimer = 0;

	spawnTimer2 = 300;
	currentTimer2 = 0;

	objectSize = 30;

	createBorder();
}

void GameScene::draw()
{
	Scene::draw();
	if (cat->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 255, 255, TEXT_CENTER, "PRESS 'SPACEBAR' TO RESTART");
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2+30, 255, 255, 255, TEXT_CENTER, "GAME OVER");
	}
	else if (cat->getIsAlive() == true)
	{
	
		drawText(155, 40, 255, 255, 255, TEXT_CENTER, "HIGH SCORE: %03d", highScore);
		drawText(210, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d",cat->getPoints());
	}
}

void GameScene::update()
{
	Scene::update();

	collisionsCheck();
	
	if (currentTimer2 > 0)
		currentTimer2--;
	if (currentTimer2 <= 0)
	{
		if (cat->getIsAlive())
		{

			foodSpawn();
		}
		currentTimer2 = spawnTimer2;
		
	}
}

void GameScene::createBorder()
{
	//top wall
	int num = 0;
	for (int i = 0; i < SCREEN_WIDTH/objectSize-3; i++)
	{
		walls = new Border();
		this->addGameObject(walls);
		walls->setPos(num + 30, 30);
		num += objectSize;
	}
	//bottom wall
	num = objectSize;
	for (int i = 0; i < SCREEN_WIDTH / objectSize - 3; i++)
	{
		walls = new Border();
		this->addGameObject(walls);
		walls->setPos( num, SCREEN_HEIGHT - (objectSize + 30));
		num += objectSize;
	}
	num = objectSize;
	//sides
	for (int i = 0; i < SCREEN_HEIGHT / objectSize - 3; i++)
	{
		walls = new Border();
		this->addGameObject(walls);
		walls->setPos(30, num);
		num += objectSize;
	}
	num = 0;
	for (int i = 0; i < SCREEN_HEIGHT / objectSize - 2; i++)
	{
		walls = new Border();
		this->addGameObject(walls);
		walls->setPos(SCREEN_WIDTH - (objectSize + 30), num + 30);
		num += objectSize;
	}
}

void GameScene::collisionsCheck()
{
	for (int i = 0; i < objects.size(); i++)
	{
		Border* walls = dynamic_cast<Border*>(objects[i]);
		Food* toy = dynamic_cast<Food*>(objects[i]);
		if (walls != NULL)
		{

			int collision = checkCollision(
				cat->getBodyX(0), cat->getBodyY(0), cat->getWidth(), cat->getHeight(),
				walls->getPosX(), walls->getPosY(), walls->getWidth(), walls->getHeight()
			);
		
			if (collision == 1)
			{
				cat->doDeath();
				deleteFood();
				break;
			}
		}
		if (toy != NULL)
		{
			int collision = checkCollision(
				toy->getPosX(), toy->getPosY(), toy->getWidth(), toy->getHeight(),
				cat->getBodyX(0), cat->getBodyY(0), cat->getWidth(), cat->getHeight());
			if (collision == 1)
			{
				toy->doRemove();
				despawnFood();
				addTail();
			}
		}
	}

}

void GameScene::deleteFood()
{
	//deletes the food
	if (cat->getIsAlive() == false)
	{
		for (int i = 0; i < foodSpawned.size(); i++)
		{
			delete foodSpawned[i];
		}
		foodSpawned.clear();
	}
	
}

void GameScene::foodSpawn()
{

	toy = new Food();
	this->addGameObject(toy);
	toy->setPos(200 + (rand() % 200), 200 + (rand() % 200));

}

void GameScene::despawnFood()
{
	int index = -1;
	for (int i = 0; i < foodSpawned.size(); i++)
	{
		if (toy == foodSpawned[i])
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		foodSpawned.erase(foodSpawned.begin() + index);
		delete toy;
	}
}

void GameScene::addTail()
{
	cat->addBodyPart();
	cat->setPoints(cat->getPoints() + 1);
	if (cat->getPoints() > highScore)
	{
		highScore = cat->getPoints();
	}
}

