#include <iostream>
#include <stdio.h>
#include "button.h"
#include "explosion.h"
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
#define ScreenWidth 1024
#define ScreenHeight 768

int init();

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;
ALLEGRO_MOUSE_STATE state;
ALLEGRO_FONT *font;
ALLEGRO_FONT *smallFont;
ALLEGRO_BITMAP *img;

int main(int argc, char **argv)
{
    init();

    ALLEGRO_SAMPLE *explosionNoise = al_load_sample("explode.wav");
    ALLEGRO_SAMPLE *startSound = al_load_sample("XP Closing sound.wav");
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());

    timer = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    font = al_load_font("courbd.ttf", 30, 0);
    smallFont = al_load_font("courbd.ttf", 20, 0);
    img = al_load_bitmap("Smiley Sprite Sheet.png");
    ALLEGRO_BITMAP *background = al_load_bitmap("background.jpg");
    explosion explosAnimation = explosion(410, 420, 64);;

    bool title = true;
    bool play = false;
    bool gameOver =false;
    bool playerWin;

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
    int curWord = 0;
    string THE_WORD = words[curWord];            // word to guess
    int wrong = 0;                               // number of incorrect guesses
    string soFar(THE_WORD.size(), '-');          // word guessed so far
    string used = "";
    string draw;
    int wordsRight = 0;
    al_play_sample(startSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

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
        if (title && event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                title = false;
                play = true;
            }
        }
        if (event.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
        }
        if (redraw && al_is_event_queue_empty(queue)) {
            al_set_target_bitmap(al_get_backbuffer(display));
            al_get_mouse_state(&state);
            al_draw_scaled_bitmap(background, 0, 0, 1280, 1024, 0, 0, ScreenWidth, ScreenHeight, 0);
            if (title)
            {
                al_draw_text(font, al_map_rgb(225, 0, 0), 230, 160, 0, "Welcome to Hangman!");
                al_draw_text(smallFont, al_map_rgb(225, 0, 0), 470, 220, ALLEGRO_ALIGN_CENTER, "Click the letters at the bottom");
                al_draw_text(smallFont, al_map_rgb(225, 0, 0), 470, 250, ALLEGRO_ALIGN_CENTER, "and try to guess the word");
                al_draw_text(smallFont, al_map_rgb(225, 0, 0), 470, 290, ALLEGRO_ALIGN_CENTER, "You gain points for every every correct letter guess");
                al_draw_text(smallFont, al_map_rgb(225, 0, 0), 470, 320, ALLEGRO_ALIGN_CENTER, "You lose point for every wrong letter guess");
                al_draw_text(smallFont, al_map_rgb(225, 0, 0), 470, 360, ALLEGRO_ALIGN_CENTER, "You win when you guess all the words");
                al_draw_text(smallFont, al_map_rgb(225, 0, 0), 470, 390, ALLEGRO_ALIGN_CENTER, "You lose when you get 8 incorrect letter guesses on the same word");
                al_draw_text(smallFont, al_map_rgb(225, 0, 0), 470, 450, ALLEGRO_ALIGN_CENTER, "Press enter to start");
            }
            if (play)
            {
                char guess;
                explosAnimation.draw();
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
                            al_play_sample(explosionNoise, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            explosAnimation.startDraw();
                        }
                    }
                }
                draw = "The word so far is " + soFar;
                al_draw_text(font, al_map_rgb(225, 0, 0), 200, 160, 0, draw.c_str());
                if (THE_WORD.compare(soFar) == 0)
                {
                    curWord++;
                    THE_WORD = words[curWord];
                    wrong = 0;
                    soFar = string(THE_WORD.size(), '-');
                    used = "";
                    wordsRight++;
                    for (int i = 0; i < buttons.size(); i++)
                    {
                        buttons[i].reset();
                    }
                }
                int headX;
                int headY;
                if (wrong <= 8)
                {
                    headX = 1;
                    headY = 1;
                    if (wrong <= 7)
                    {
                        al_draw_line(440, 264, 440, 364, al_map_rgb(255, 255, 255), 3);
                        if (wrong <= 6)
                        {
                            headY = 0;
                            if (wrong <= 5)
                            {
                                al_draw_line(440, 304, 480, 294, al_map_rgb(255, 255, 255), 3);
                                if (wrong <= 4)
                                {
                                    al_draw_line(440, 304, 400, 294, al_map_rgb(255, 255, 255), 3);
                                    if (wrong <= 3)
                                    {
                                        headX = 0;
                                        if (wrong <= 2)
                                        {
                                            al_draw_line(440, 364, 470, 400, al_map_rgb(255, 255, 255), 3);
                                            if (wrong <= 1)
                                            {
                                                al_draw_line(440, 364, 410, 400, al_map_rgb(255, 255, 255), 3);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    al_draw_scaled_bitmap(img, headX*72, headY*72, 72, 72, 400, 200, 64, 64, 0);
                }
                if (wrong == 8)
                {
                    play = false;
                    gameOver = true;
                }
            }
            if (gameOver)
            {
                al_draw_text(font, al_map_rgb(225, 0, 0), 230, 160, 0, "You lost!");
                al_draw_textf(smallFont, al_map_rgb(225, 0, 0), 470, 500, ALLEGRO_ALIGN_CENTER, "You got %d words right", wordsRight);
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
