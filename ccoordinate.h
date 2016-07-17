#ifndef CCOORDINATE_H
#define CCOORDINATE_H
#include <iostream>
class cCoordinate
{
private:
    int x, y;
public:
    cCoordinate()
    {
        x = 0; y = 0;
    }
    cCoordinate(int ix, int iy)
    {
        x = ix; y = iy;
    }
    inline int getX() { return x; }
    inline int getY() { return y; }
    bool operator==(cCoordinate c)
    {
        if (this->x == c.x && this->y == c.y)
            return true;
        else
            return false;
    }
    cCoordinate operator+(cCoordinate c)
    {
        cCoordinate a;
        a.set(x + c.x, y + c.y);
        return a;
    }
    void operator+=(cCoordinate c)
    {
        set(x + c.x, y + c.y);
    }
    void add(int ix, int iy)
    {
        set(x + ix, y + iy);
    }
    cCoordinate * operator=(cCoordinate * c)
    {
        this->x = c->x;
        this->y = c->y;
        return this;
    }
    void set(int ix, int iy)
    {
        x = ix; y = iy;
    }

    friend std::ostream & operator<<(std::ostream & o, cCoordinate c)
    {
        o << "[" << c.x << ", " << c.y << "]";
        return o;
    }
};
#endif // CCOORDINATE_H
