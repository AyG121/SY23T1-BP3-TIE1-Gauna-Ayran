#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new PlayerShip();
	this->addGameObject(player);

	points = 0;
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
	initFonts();
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

	drawText(110, 20, 255, 255, 255, TEXT_CENTER,"POINTS: %03d",points);

	if (player->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "GAME OVER");
	}
}

void GameScene::update()
{
	Scene::update();
	doCollisionCheck();
	doCollisionCheck();
}

void GameScene::doSpawnCheck()
{

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

void GameScene::doCollisionCheck()
{
	//collision check
	for (int i = 0; i < objects.size(); i++)
	{
		Bullet* bullet = dynamic_cast <Bullet*>(objects[i]);

		//cast success check
		if (bullet != NULL)
		{
			//checks enemy bullet
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
				);

				if (collision == 1)
				{
					player->doDeath();
					break;
				}
			}
			//player bullet
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemy.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemy[i];


					int collision = checkCollision(
						currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);
					if (collision == 1)
					{
						despawnEnemy(currentEnemy);
						currentEnemy->doDeath();
						points++;
						break;
					}
				}
			}
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

void GameScene::despawnEnemy(Enemy* enemy)
{
	int index = -1;
	for (int i = 0; i < spawnedEnemy.size(); i++)
	{
		//pointer match
		if (enemy == spawnedEnemy[i]) 
		{
			index = i;
			break;
		}
	}
		if (index != 1)
		{
			spawnedEnemy.erase(spawnedEnemy.begin() + index);
			delete enemy;
		}
}
