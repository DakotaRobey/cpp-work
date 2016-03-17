#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"

class background
{
    public:
        background();
        virtual ~background();
        void draw();
    protected:
    private:
        ALLEGRO_BITMAP *img;
};

#endif // BACKGROUND_H
