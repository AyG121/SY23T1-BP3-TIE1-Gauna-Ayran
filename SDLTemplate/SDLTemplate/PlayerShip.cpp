#include "PlayerShip.h"

void PlayerShip::start()
{
	//loading textures
	texture = loadTexture("gfx/player.png");

	//data initialization
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	speed = 2;
	accelerate = 5;
	slowDown-=accelerate;
	//query
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void PlayerShip::update()
{
	
	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= speed;
	}
	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}
	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}
	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}
	//make the ship go speed there is probably a smarter way to do this but I refuse to think
	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{

		speed+=accelerate;
	}
	//sl o w
	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{

		speed+=slowDown;
	}
}

void PlayerShip::draw()
{
	blit(texture, x, y);
}
