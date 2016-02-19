#include <iostream>
#include <stdio.h>
#include "button.h"
#include <algorithm>

#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include <vector>
//Dynamic Link
#define ScreenWidth 640
#define ScreenHeight 480

int init();

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;
ALLEGRO_MOUSE_STATE state;
ALLEGRO_FONT *font;

int main(int argc, char **argv)
{
    init();
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());

    timer = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    font = al_load_font("courbd.ttf", 20, 0);

    vector<button> buttons;
    int x = 140;
    int y = 350;
    for (unsigned char c = 65; c <= 90; ++c)
    {
        buttons.push_back(button(x, y, 30, string(1, c)));
        x += 30;
        if (x > 500)
        {
            x = 140;
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
    words.push_back("");

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
            char guess;

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
                        wrong++;
                    }
                }
            }

            draw = "The word so far is " + soFar;
            al_draw_text(font, al_map_rgb(255, 0, 0), 30, 30, 0, draw.c_str());

            al_flip_display();
        }
    }
    al_destroy_display(display);

    /*const int MAX_WRONG = 8;  // maximum number of incorrect guesses allowed

    vector<string> words;  // collection of possible words to guess
    words.push_back("GUESS");
    words.push_back("HANGMAN");
    words.push_back("DIFFICULT");
    words.push_back("MINESWEEPER");
    words.push_back("ENGINEER");
    words.push_back("EXPLOSION");
    words.push_back("CHANCE");
    words.push_back("");

	srand(time(0));
    random_shuffle(words.begin(), words.end());
    const string THE_WORD = words[0];            // word to guess
    int wrong = 0;                               // number of incorrect guesses
    string soFar(THE_WORD.size(), '-');          // word guessed so far
    string used = "";                            // letters already guessed



    // main loop
    while ((wrong < MAX_WRONG) && (soFar != THE_WORD))
    {
        cout << "\n\nYou have " << (MAX_WRONG - wrong) << " incorrect guesses left.\n";
        cout << "\nYou've used the following letters:\n" << used << endl;
        cout << "\nSo far, the word is:\n" << soFar << endl;

        char guess;
        cout << "\n\nEnter your guess: ";
        cin >> guess;
        guess = toupper(guess); //make uppercase since secret word in uppercase
        while (used.find(guess) != string::npos)
        {
            cout << "\nYou've already guessed " << guess << endl;
            cout << "Enter your guess: ";
            cin >> guess;
            guess = toupper(guess);
        }

        used += guess;

        if (THE_WORD.find(guess) != string::npos)
        {
            cout << "That's right! " << guess << " is in the word.\n";

            // update soFar to include newly guessed letter
            for (int i = 0; i < THE_WORD.length(); ++i)
                if (THE_WORD[i] == guess)
                    soFar[i] = guess;
        }
        else
        {
            cout << "Sorry, " << guess << " isn't in the word.\n";
            ++wrong;
        }
    }

    // shut down
    if (wrong == MAX_WRONG)
        cout << "\nYou've been hanged!";
    else
        cout << "\nYou guessed it!";

    cout << "\nThe word was " << THE_WORD << endl;*/

    return 0;
}

int init(){

    if(!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    display = al_create_display(640, 480);
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
