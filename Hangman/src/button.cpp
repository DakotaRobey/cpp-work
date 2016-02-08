#include "button.h"

button::button()
{
    x = 0;
    y = 0;
    height = 30;
    width = 30;
    text = "!";
    clicked = false;
}

button::button(int xCord, int yCord, int tallness, int wideness, string letter)
{
    x = xCord;
    y = yCord;
    height = tallness;
    width = wideness;
    text = letter;
    clicked = false;
}

void button::draw()
{
    al_draw_filled_rectangle(x, y, x+height, y+height, al_map_rgb(255, 98, 100), 9.0);
    al_draw_textf();
}

bool button::isClicked()
{
    return clicked;
}
