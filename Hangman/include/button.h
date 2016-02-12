#ifndef BUTTON_H
#define BUTTON_H
#include <string>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"

using namespace std;

class button
{
    public:
        button();
        button(int, int, int, string);
        bool isClicked();
        void draw();
    protected:
    private:
        int x;
        int y;
        int height;
        int width;
        string text;
        bool mouseHover;
        bool clicked;
        ALLEGRO_FONT *font;

};

#endif // BUTTON_H
