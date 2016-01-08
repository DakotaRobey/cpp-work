#include "ocean.h"


ocean::ocean()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            shots[i][j] = false;
        }
    }
}

bool ocean::getShot(int x, int y)
{
    return shots[x-1][y-1];
}

int ocean::shotsFired(int x, int y)
{
    if (!shots[x-1][y-1])
    {
        shots[x-1][y-1] = true;
        return 0;
    }
    else
        return -1;
}

void ocean::draw()
{
    int offset = 15;
    int side = 20;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            al_draw_rectangle((i*side)+offset, (j*side)+offset, (i*side)+side+offset, (j*side)+side+offset, al_map_rgb(255, 255, 255), 1.0);
            if(shots[i][j])
            {
                al_draw_filled_rectangle((i*side)+offset, (j*side)+offset, (i*side)+side+offset, (j*side)+side+offset, al_map_rgb(255, 98, 100));
            }
        }
    }
}
