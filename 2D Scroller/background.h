#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include <vector>
#include "floater.h"

class background
{
    public:
        background();
        void draw();
        void addSprite();
        int numSprites();
    protected:
    private:
        ALLEGRO_BITMAP *img;
        int camX;
        std::vector<floater> sprites;
};

#endif // BACKGROUND_H
