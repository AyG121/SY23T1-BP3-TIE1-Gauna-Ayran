#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	background = new Background();
	this->addGameObject(background);
	//player
	player = new PlayerShip();
	this->addGameObject(player);

	points = 0;
	bossHp = 30;
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
	currentSpawnTimer = 200;
	spawnTime = 200;
	//20s to spawn boss
	bossSpawnTime=1000;
	currentBossSpawnTimer=1000;
	
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
	doSpawnCheck();
}

void GameScene::doSpawnCheck()
{
	if (currentSpawnTimer > 0)
		currentSpawnTimer--;
	if (currentSpawnTimer <= 0 && bossFight == false)
	{
		for (int i = 0; i < 3; i++)
		{
			spawner();
			currentSpawnTimer = spawnTime;
		}
		powerUpSpawn();
	}

	if (currentBossSpawnTimer > 0)
		currentBossSpawnTimer--;
	if (currentBossSpawnTimer <= 0) 
	{
		for (int i = 0; i < 1; i++)
		{
			bossFight = true;
			createBoss();
			bossHp++;
			currentBossSpawnTimer = bossSpawnTime;
			break;
		}
	}
	
}

void GameScene::doCollisionCheck()
{
	//collision check
	for (int i = 0; i < objects.size(); i++)
	{
		Bullet* bullet = dynamic_cast <Bullet*>(objects[i]);
		PowerUps* powerUp = dynamic_cast<PowerUps*>(objects[i]);
		Boss* boss = dynamic_cast<Boss*>(objects[i]);
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
						Explosion* explode = new Explosion();

						this->addGameObject(explode);
						explode->getEnemyLocation(currentEnemy);
						explode->setPosition(currentEnemy->getPositionX(), currentEnemy->getPositionY());

						despawnEnemy(currentEnemy);
						points++;
						break;
					}

				}
				for (int i = 0; i < spawnedBoss.size(); i++)
				{
					Boss* currentBoss = spawnedBoss[i];


					int collision = checkCollision(
						currentBoss->getPositionX(), currentBoss->getPositionY(), currentBoss->getWidth(), currentBoss->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()

					);
					if (collision == 1)
					{
						/*
						Explosion* explode = new Explosion();

						this->addGameObject(explode);
						explode->getBossLocation(currentBoss);
						explode->setPosition(currentBoss->getPositionX(), currentBoss->getPositionY());
						*/
						bossHp--;

						if (bossHp <= 0)
						{
						despawnBoss(currentBoss);
						bossFight = false;
						break;
						}
						points++;
						break;
					}
				}
			}
		}

		if (powerUp != NULL)
		{
			int collision = checkCollision(
				powerUp->getPositionX(), powerUp->getPositionY(), powerUp->getWidth(), powerUp->getHeight(),
				player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight()
			);
			if (collision == 1)
			{
				player->usePowerUp();
				powerUp->doRemove();//doesn't respawn and delete
				delete powerUp;
			}
		}
		
	}
}

void GameScene::spawner()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->getPlayerTarget(player);
	enemy->setPosition(300 + (rand() % 300),30 );
	spawnedEnemy.push_back(enemy);
}

void GameScene::powerUpSpawn()
{
	//power up
	powerUp = new PowerUps();
	this->addGameObject(powerUp);
	powerUp->setPosition(200 + (rand() % 200), 0);
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
	if (index != -1)
	{
		spawnedEnemy.erase(spawnedEnemy.begin() + index);
		delete enemy;
	}
}

void GameScene::createBoss()
{
	//boss
	Boss* boss = new Boss();
	this->addGameObject(boss);
	boss->getPlayerTarget(player);
	boss->setPosition(300, 300);
	spawnedBoss.push_back(boss);
}

void GameScene::despawnBoss(Boss* boss)
{
	int index = -1;
	for (int i = 0; i < spawnedBoss.size(); i++)
	{
		//pointer match
		if (boss == spawnedBoss[i])
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		spawnedBoss.erase(spawnedBoss.begin() + index);
		delete boss;
	}
}
