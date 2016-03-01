#include <iostream>
#include <stdio.h>
#include "button.h"
#include <algorithm>

#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include <vector>
//Dynamic Link
//Credit to drew barrett the best coder that i, dakota robey have ever met
#define ScreenWidth 1024
#define ScreenHeight 768

int init();

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;
ALLEGRO_MOUSE_STATE state;
ALLEGRO_FONT *font;
ALLEGRO_BITMAP *img;
;

int main(int argc, char **argv)
{
    init();

    ALLEGRO_SAMPLE *explosion = al_load_sample("explode.wav");
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());

    timer = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    font = al_load_font("courbd.ttf", 30, 0);
    img = al_load_bitmap("Smiley Sprite Sheet.png");
    ALLEGRO_BITMAP *background = al_load_bitmap("background.jpg");

    bool title = false;
    bool play = true;
    bool gameOver =false;

    vector<button> buttons;
    int x = 250;
    int y = 546;
    for (unsigned char c = 65; c <= 90; ++c)
    {
        buttons.push_back(button(x, y, 30, string(1, c)));
        x += 30;
        if (x > 610)
        {
            x = 250;
            y += 30;
        }
    }
    const int MAX_WRONG = 8;  // maximum number of incorrect guesses allowed

    vector<string> words;  // collection of possible words to guess
    words.push_back("GUESS");
    words.push_back("HANGMAN");
    words.push_back("DIFFICULT");
    words.push_back("MINESWEEPER");
    words.push_back("ENGINEER");
    words.push_back("EXPLOSION");
    words.push_back("CHANCE");
    words.push_back("SUNGLASSES");

	srand(time(0));
    random_shuffle(words.begin(), words.end());
    string THE_WORD = words[0];            // word to guess
    int wrong = 0;                               // number of incorrect guesses
    string soFar(THE_WORD.size(), '-');          // word guessed so far
    string used = "";
    string draw;

    while (1) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        al_clear_to_color(al_map_rgb(0,0,0));
        bool redraw = true;

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                break;
        }
        if (event.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
        }
        if (redraw && al_is_event_queue_empty(queue)) {
            al_set_target_bitmap(al_get_backbuffer(display));
            al_get_mouse_state(&state);
            if (play)
            {
                char guess;
                al_draw_scaled_bitmap(background, 0, 0, 1280, 1024, 0, 0, ScreenWidth, ScreenHeight, 0);
                for (int i = 0; i < buttons.size(); i++)
                {
                    buttons[i].draw(state, al_mouse_button_down(&state, 1));
                    if ((used.find(buttons[i].getLetter()) == string::npos) && buttons[i].isHighlighted() && buttons[i].isClicked())
                    {
                        guess = buttons[i].getLetter()[0];
                        guess = toupper(guess); //make uppercase since secret word in uppercase
                        used += guess;
                        if (THE_WORD.find(guess) != string::npos)
                        {
                            buttons[i].setCorrectness(true);
                            for (int i = 0; i < THE_WORD.length(); ++i)
                            {
                                if (THE_WORD[i] == guess)
                                {
                                    soFar[i] = guess;
                                }
                            }
                        }
                        else
                        {
                            buttons[i].setCorrectness(false);
                            wrong++;
                            al_play_sample(explosion, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        }
                    }
                }
                draw = "The word so far is " + soFar;
                al_draw_text(font, al_map_rgb(225, 0, 0), 200, 160, 0, draw.c_str());
                if (wrong <= 8)
                {
                    al_draw_scaled_bitmap(img, 72, 72, 72, 72, 260, 130, 64, 64, 0);
                    if (wrong <= 7)
                    {
                        al_draw_line(303, 187, 303, 256, al_map_rgb(255, 255, 255), 3);
                    }
                }
            }
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
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(5);
}
