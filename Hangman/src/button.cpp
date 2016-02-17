#include "button.h"

button::button()
{
    x = 0;
    y = 0;
    height = 30;
    text = "!";
    beenClicked = false;
    font = al_load_font("courbd.ttf", 20, 0);
}

button::button(int xCord, int yCord, int tallness, string letter)
{
    x = xCord;
    y = yCord;
    height = tallness;
    text = letter;
    beenClicked = false;
    font = al_load_font("courbd.ttf", 2*(tallness/3), 0);
}

void button::draw(ALLEGRO_MOUSE_STATE mouse, bool clicked)
{
    if (clicked)
    {
        beenClicked = true;
    }
    if (beenClicked)
    {
        al_draw_filled_rectangle(x, y, x+height, y+height, al_map_rgb(61, 61, 61));
    }
    else if ((mouse.x > x && mouse.x < x+height) && (mouse.y > y && mouse.y < y+height))
    {
        al_draw_filled_rectangle(x, y, x+height, y+height, al_map_rgb(0, 125, 255));
    }
    else
    {
        al_draw_filled_rectangle(x, y, x+height, y+height, al_map_rgb(255, 0, 0));
    }

    al_draw_text(font, al_map_rgb(0, 255, 0), x+(height/3), y+(height/5), 0, text.c_str());
}

bool button::isClicked()
{
    return beenClicked;
}
