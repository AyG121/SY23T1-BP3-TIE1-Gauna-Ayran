#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "PlayerShip.h"
#include"Enemy.h"
#include<vector>
#include"text.h"
#include"Background.h"
#include"Explosion.h"
#include"PowerUps.h"
#include"Boss.h"
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	PlayerShip* player;
	Enemy* enemy;
	Background* background;
	Explosion* explode;
	PowerUps* powerUp;
	Boss* boss;
	//enemy spawner
	float spawnTime;
	float currentSpawnTimer;
	std::vector<Enemy*> spawnedEnemy;

	void doSpawnCheck();
	void doCollisionCheck();
	void spawner();
	void powerUpSpawn();
	void despawnEnemy(Enemy* enemy);
	int points;
	//boss spawner functions
	float bossSpawnTime;
	float currentBossSpawnTimer;
	void createBoss();
	void despawnBoss(Boss* boss);
	std::vector<Boss*> spawnedBoss;
	int bossHp;
	bool bossFight;
};

