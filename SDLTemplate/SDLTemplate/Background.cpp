#include "Background.h"

void Background::start()
{
	//loading textures
	texture = loadTexture("gfx/background.png");
	width = 0;
	height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Background::update()
{
}

void Background::draw()
{
	blitScale(texture, 00, 00, &width, &height, 4);
}
