#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <string>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include <iostream>
#include <stdio.h>
#include <vector>


class explosion
{
    public:
        explosion();
        explosion(int, int, int);
        void draw();
    protected:
    private:
        int x;
        int y;
        int width;
        ALLEGRO_BITMAP *parent;
        int frame;
        int frameDelay;
        int frameCount;
        std::vector<ALLEGRO_BITMAP*> frames;
};

#endif // EXPLOSION_H
