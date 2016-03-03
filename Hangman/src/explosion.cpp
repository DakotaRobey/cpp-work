#include "explosion.h"

explosion::explosion()
{
    x = 0;
    y = 0;
    width = 64;
    parent = al_load_bitmap("explosion spritesheet.png");
    frame = 0;
    frameDelay = 2;
    frameCount = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            frames[frame] = al_create_sub_bitmap(parent, j*56, i*56, 56, 56);
            frame++;
        }
    }
    frame = 0;
}

explosion::explosion(int drawX, int drawY, int sideLength)
{
    x = drawX;
    y = drawY;
    width = sideLength;
    parent = al_load_bitmap("explosion spritesheet.png");
    frame = 0;
    frameDelay = 2;
    frameCount = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            frames[frame] = al_create_sub_bitmap(parent, j*56, i*56, 56, 56);
            frame++;
        }
    }
    frame = 0;
}

void explosion::draw()
{
    if (frameCount <= frameDelay)
    {
        al_draw_scaled_bitmap(frames[frame], 0, 0, 56, 56, x, y, width, width, 0);
        frameCount++;
    }
    else
    {
        frame++;
        al_draw_scaled_bitmap(frames[frame], 0, 0, 56, 56, x, y, width, width, 0);
        frameCount = 0;
    }
}
