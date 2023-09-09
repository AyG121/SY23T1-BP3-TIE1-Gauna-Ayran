#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "PlayerShip.h"

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
};

