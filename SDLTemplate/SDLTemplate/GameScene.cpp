#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new PlayerShip();
	this->addGameObject(player);
}

GameScene::~GameScene()
{
	delete player;
	delete enemy;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	currentSpawnTimer = 300;
	spawnTime = 300;

	for (int i = 0; i < 3; i++)
	{
		spawner();
	}
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();

	if (currentSpawnTimer > 0)
		currentSpawnTimer--;
	if (currentSpawnTimer <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			spawner();
		 currentSpawnTimer = spawnTime;
		}
	}
}

void GameScene::spawner()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->getPlayerTarget(player);
	enemy->setPosition(1200, 300 + (rand() % 300));
	spawnedEnemy.push_back(enemy);

	
}
