#ifndef OCEAN_H
#define OCEAN_H
#include "ship.h"


class ocean
{
    public:
        ocean();
        bool getShot(int,int);
        int shotsFired(int,int);
        void draw();
    protected:
    private:
        bool shots[10][10];

};

#endif // OCEAN_H
