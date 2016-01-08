#ifndef SHIP_H
#define SHIP_H
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"

class ship
{
    public:
        ship(int);
        bool getDestroyed();
        int getSize();
    protected:
    private:
        int hitPoints;
        int sSize;
        bool destroyed;
};

#endif // SHIP_H
