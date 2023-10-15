#include "PlayerShip.h"
#include "draw.h"
#include "Scene.h"
#include "PowerUps.h"
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
	x = 350;
	y = 550;
	width = 0;
	height = 0;
	speed = 2;
	accelerate = 5;
	slowDown -= accelerate;
	reloadTime = 20;
	currentReloadTime = 0;
	secondReloadTime = 0;
	isAlive = true;
	powerUpCheck = false;
	//query
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg" );
}

void PlayerShip::update()
{
	//delete
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
		{
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;
		}
	}

	if (!isAlive) return;

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

	
	if (powerUpCheck==true)
	{
		if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
		{
			SoundManager::playSound(sound);
			Bullet* powerBullet = new Bullet(5+(x - 3 + width / 2), y - 25 + height / 2, 0, -1, 10, Side::PLAYER_SIDE);
			Bullet* powerBullet2 = new Bullet(-5+(x - 3 + width / 2), y - 25 + height / 2, 0, -1, 10, Side::PLAYER_SIDE);
			bullets.push_back(powerBullet);
			bullets.push_back(powerBullet2);
			getScene()->addGameObject(powerBullet);
			getScene()->addGameObject(powerBullet2);
			currentReloadTime = reloadTime - 5;
		}
	}
	else
	{
		if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
		{
			SoundManager::playSound(sound);
			Bullet* bullet = new Bullet(x - 3 + width / 2, y - 25 + height / 2, 0, -1, 10, Side::PLAYER_SIDE);
			bullets.push_back(bullet);
			getScene()->addGameObject(bullet);
			currentReloadTime = reloadTime;
		}
	}
	//extra gun
	if (app.keyboard[SDL_SCANCODE_G] && currentReloadTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* secondCanon = new Bullet(15 +(x-3 + width / 2), y + height / 2, 0, -1, 10, Side::PLAYER_SIDE);
		Bullet* secondCanon2 = new Bullet(-15 +(x-3 + width / 2), y + height / 2, 0, -1, 10, Side::PLAYER_SIDE);
		bullets.push_back(secondCanon);
		bullets.push_back(secondCanon2);
		getScene()->addGameObject(secondCanon);
		getScene()->addGameObject(secondCanon2);
		currentReloadTime = reloadTime-10;
	}

}

void PlayerShip::draw()
{
	if (isAlive)
	{
		blit(texture, x, y);
	}
	
}

int PlayerShip::getPositionX()
{
	return x;
}

int PlayerShip::getPositionY()
{
	return y;
}

int PlayerShip::getWidth()
{
	return width;
}

int PlayerShip::getHeight()
{
	return height;
}

void PlayerShip::usePowerUp()
{
	//and add skill then remove skill after awhile
	powerUpCheck = true;
	//grab collided check power up state if taken or not taken
	//have condition when press f and the powerup state = collided
	//it shoot 2 bollet
	//cooldown/time thing

}

bool PlayerShip::getIsAlive()
{
	return isAlive;
}

void PlayerShip::doDeath()
{
	isAlive = false;
}


