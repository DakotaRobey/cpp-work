#ifndef SHIP_H
#define SHIP_H


class ship
{
    public:
        ship(int size);
        boolean isDestroyed();
        virtual ~ship();
    protected:
    private:
        boolean hitPoints[];
        boolean destroyed;
};

#endif // SHIP_H
