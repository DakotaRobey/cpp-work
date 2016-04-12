#ifndef FLOATER_H
#define FLOATER_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "iostream"

class floater
{
    public:
        floater(int, int);
        void draw();
    protected:
    private:
        int x;
        int y;
        int sidelength;
        int sprite;
        ALLEGRO_BITMAP *source;
};

#endif // FLOATER_H
