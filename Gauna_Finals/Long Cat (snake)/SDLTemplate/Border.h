#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "util.h"
class Border : public GameObject
{
public:

    void start();
    void update();
    void draw();

    void setPos(int posX, int posY);

    int getPosX();
    int getPosY();
    int getWidth();
    int getHeight();

private:
    SDL_Texture* texture;

    int posX;
    int posY;
    int width;
    int height;

};

