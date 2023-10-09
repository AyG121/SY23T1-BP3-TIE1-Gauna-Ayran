#pragma once
#include "GameObject.h"
#include"SDL.h"
#include "common.h"
#include "draw.h"
class Background : public GameObject
{
public:
	void start();
	void update();
	void draw();
private:
	SDL_Texture* texture;
	int width;
	int height;
};

