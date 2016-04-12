#include <iostream>
#include <stdio.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "background.h"
//Dynamic Link
#define ScreenWidth 1024
#define ScreenHeight 768
int init();
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;
ALLEGRO_KEYBOARD_STATE *key;

using namespace std;

int main(int argc, char **argv)
{
    cout << "Keyboard state created" << endl;
    ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
    ALLEGRO_COLOR electricBlue = al_map_rgb(44, 117, 255);
    init();
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());

    timer = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    background ocean = background();
    int maxSprites = 10;
    int dFrames = 0;
    srand (time(0));

    while (1) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        al_get_keyboard_state(key);
        cout << "keyboard state saved" << endl;
        bool redraw = true;

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                break;
        }
        if (al_key_down(key, ALLEGRO_KEY_UP))
        {
            ocean.movePlayer(-8);
        }
        if (al_key_down(key, ALLEGRO_KEY_DOWN))
        {
            ocean.movePlayer(8);
        }
        if (event.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
            dFrames++;
        }

        if (redraw && al_is_event_queue_empty(queue)) {
            al_set_target_bitmap(al_get_backbuffer(display));
            redraw = false;
            if (dFrames >= 60 && ocean.numSprites() < maxSprites)
            {
                ocean.addSprite();
                dFrames = 0;
                std::cout << "called addsprite()" << std::endl;
            }
            ocean.draw();
            al_flip_display();
        }
    }
    al_destroy_display(display);
    return 0;
}

int init(){

    if(!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    display = al_create_display(ScreenWidth, ScreenHeight);
    if(!display)
    {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
    al_clear_to_color(al_map_rgb(0,0,0));
    al_init_image_addon();
    if(!al_init_primitives_addon()){
        fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_mouse();
    al_install_keyboard();
}
