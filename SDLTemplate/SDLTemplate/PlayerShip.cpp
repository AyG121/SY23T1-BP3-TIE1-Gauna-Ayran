#include "PlayerShip.h"
#include "draw.h"
#include "Scene.h"
PlayerShip::~PlayerShip()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear();
}
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
	slowDown -= accelerate;
	reloadTime = 20;
	currentReloadTime = 0;
	secondReloadTime = 0;
	//query
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg" );
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
	//reload
	if (currentReloadTime > 0)
		currentReloadTime--;

	//fire sound
	if (app.keyboard[SDL_SCANCODE_F]&& currentReloadTime==0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x+width,y-2+height/2,1,0,10);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();
		currentReloadTime = reloadTime;
	}
	//extra gun
	if (app.keyboard[SDL_SCANCODE_G] && currentReloadTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* secondCanon = new Bullet(x-5 + width/2, y-10, 1, 0, 10);
		Bullet* secondCanon2 = new Bullet(x-5 + width/2, y+40, 1, 0, 10);
		bullets.push_back(secondCanon);
		bullets.push_back(secondCanon2);
		getScene()->addGameObject(secondCanon);
		getScene()->addGameObject(secondCanon2);
		secondCanon->start();
		secondCanon2->start();
		currentReloadTime = reloadTime-10;
	}
	//delete
	for (int i = 0; i < bullets.size();i++) 
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
		{
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;
		}
	}
}

void PlayerShip::draw()
{
	blit(texture, x, y);
}
