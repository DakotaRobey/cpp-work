#include "explosion.h"

explosion::explosion()
{
    x = 0;
    y = 0;
    width = 64;
    parent = al_load_bitmap("explosion spritesheet.png");
    frameX = 0;
    frameY = 0;
    frameDelay = 2;
    frameCount = 0;
    play = false;
}

explosion::explosion(int drawX, int drawY, int sideLength)
{
    x = drawX;
    y = drawY;
    width = sideLength;
    parent = al_load_bitmap("explosion spritesheet.png");
    frameX = 0;
    frameY = 0;
    frameDelay = 3;
    frameCount = 0;
    play = false;
}

void explosion::draw()
{
    if (play)
    {
        al_draw_scaled_bitmap(parent, frameX*56, frameY*56, 56, 56, x, y, width, width, 0);
        if (frameCount <= frameDelay)
        {
            frameCount++;
        }
        else
        {
            frameX++;
            if (frameX == 4)
            {
                frameX = 0;
                frameY++;
            }
            frameCount = 0;
        }
    }
    if (frameY == 4)
    {
        play = false;
        frameX = 0;
        frameY = 0;
    }
}

void explosion::startDraw()
{
    play = true;
}
