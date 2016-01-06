#include "ocean.h"

ocean::ocean()
{
    shots[10][10];
    ships[5];
    ships[0] = new ship(3);
    for (int i = 1; i < 4)
    {
        ships[i] = new ship(i+1);
    }
}

ocean::~ocean()
{
    //dtor
}
