#include "background.h"

background::background()
{
    img = al_load_bitmap("Ocean.png");
    player = al_load_bitmap("playerfixed.png");
    camX = 0;
    srand (time(0));
    playerY = 768/2;
}

void background::draw()
{
    std::cout << "drew the background" << std::endl;
    al_draw_scaled_bitmap(img, camX%1024, 0, 1024, 768, 0, 0, 1024, 768, 0);
    al_draw_scaled_bitmap(player, 0, 0, 192, 192, 50, playerY, 64, 64, 0);
    camX++;
    for (int i = 0; i < sprites.size(); i++)
    {
        if (sprites[i].getX() < -64)
        {
            sprites.erase(sprites.begin());
        }
        sprites[i].draw();
    }
}

void background::addSprite()
{
    std::cout << "added a sprite" << std::endl;
    sprites.push_back(floater(rand()%604+100, rand()%3));
}

int background::numSprites()
{
    return sprites.size();
}

void background::movePlayer(int direction)
{
    playerY += direction;
}
