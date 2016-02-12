#include "button.h"

button::button()
{
    x = 0;
    y = 0;
    height = 30;
    text = "!";
    clicked = false;
    font = al_load_font("courbd.ttf", 12, 0);
}

button::button(int xCord, int yCord, int tallness, string letter)
{
    x = xCord;
    y = yCord;
    height = tallness;
    text = letter;
    clicked = false;
    font = al_load_font("courbd.ttf", 12, 0);
}

void button::draw()
{
    al_draw_filled_rectangle(x, y, x+height, y+height, al_map_rgb(255, 0, 0));
    al_draw_text(font, al_map_rgb(0, 255, 0), x+(height/2), y+(height/2), 0, text.c_str());
}

bool button::isClicked()
{
    return clicked;
}
