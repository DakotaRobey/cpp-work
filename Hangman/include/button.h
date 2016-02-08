#ifndef BUTTON_H
#define BUTTON_H
#include <string>

using namespace std;

class button
{
    public:
        button();
        button(int, int, int, int, string);
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

};

#endif // BUTTON_H
