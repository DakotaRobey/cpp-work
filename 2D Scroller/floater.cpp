#include "floater.h"

floater::floater(int genY, int genSprite)
{
    source = al_load_bitmap("Sprites.png");
    x = 1024;
    y = genY;
    sidelength = 64;
    sprite = genSprite;
}

void floater::draw()
{
    al_draw_scaled_bitmap(source, sprite*192, 0, 192, 192, x, y, sidelength, sidelength, 0);
    x -= 4;
    std::cout << "drawing a sprite " << x << " " << y << std::endl;
}

int floater::getX()
{
    return x;
}
