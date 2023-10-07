#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "PlayerShip.h"
#include"Enemy.h"
#include<vector>
#include"text.h"
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

	//enemy spawner
	float spawnTime;
	float currentSpawnTimer;
	std::vector<Enemy*> spawnedEnemy;

	void doSpawnCheck();
	void doCollisionCheck();
	void spawner();
	void despawnEnemy(Enemy* enemy);

	int points;
};

