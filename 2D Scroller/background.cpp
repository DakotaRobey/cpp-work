#include "background.h"

background::background()
{
    img = al_load_bitmap("Ocean.png");
    camX = 0;
    srand (time(0));
}

void background::draw()
{
    std::cout << "drew the background" << std::endl;
    al_draw_scaled_bitmap(img, camX%1024, 0, 1024, 768, 0, 0, 1024, 768, 0);
    camX++;
    for (int i = 0; i < sprites.size(); i++)
    {
        sprites[i].draw();
    }
}

void background::addSprite()
{
    std::cout << "added a sprite" << std::endl;
    sprites.push_back(floater(rand()%768, rand()%3));
}

int background::numSprites()
{
    return sprites.size();
}
