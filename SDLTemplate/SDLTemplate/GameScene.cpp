#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new PlayerShip();
	this->addGameObject(player);

	enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->getPlayerTarget(player);

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
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();
}
