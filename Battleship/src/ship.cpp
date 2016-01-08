#include "ship.h"

ship::ship(int length)
{
    sSize = length;
    hitPoints = sSize;
    destroyed = false;
}

bool ship::getDestroyed()
{
    return destroyed;
}

int ship::getSize()
{
    return hitPoints;
}
