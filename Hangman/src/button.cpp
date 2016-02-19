#include "button.h"

button::button()
{
    x = 0;
    y = 0;
    height = 64;
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
    img = al_load_bitmap("images.png");
}

void button::draw(ALLEGRO_MOUSE_STATE mouse, bool clicked)
{
    if ((mouse.x > x && mouse.x < x+height) && (mouse.y > y && mouse.y < y+height))
    {
        if (clicked)
        {
            beenClicked = true;
        }
        else
        {
            al_draw_filled_rectangle(x, y, x+height, y+height, al_map_rgb(61, 61, 61));
            al_draw_text(font, al_map_rgb(255, 0, 0), x+(height/3), y+(height/5), 0, text.c_str());
        }
    }
    else
    {
        al_draw_scaled_bitmap(img, 0, 0, 64, 64, x, y, height, height, 0);
        al_draw_text(font, al_map_rgb(255, 0, 0), x+(height/3), y+(height/5), 0, text.c_str());
        //al_draw_filled_rectangle(x, y, x+height, y+height, al_map_rgb(255, 0, 0));
    }
    if (beenClicked)
    {
        al_draw_scaled_bitmap(img, 128, 0, 64, 64, x, y, height, height, 0);
        //al_draw_filled_rectangle(x, y, x+height, y+height, al_map_rgb(61, 61, 61));
    }
}

bool button::isClicked()
{
    return beenClicked;
}

void button::reset()
{
    beenClicked = false;
}

string button::getLetter()
{
    return text;
}
