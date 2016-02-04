#ifndef BUTTON_H
#define BUTTON_H


class button
{
    public:
        button();
        bool isClicked();
        void draw()
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
