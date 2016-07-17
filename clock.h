#ifndef CBLOCK_H
#define CBLOCK_H
class cBlock
{
private:
    int type;
    int dir;
    int width;
    int length;
    cCoordinate startPos;
    cCoordinate pos[4];
    int color;
public:
    cBlock()
    {
        type = rand() % 7 + 1;
        dir = rand() % 4 + 1;
        startPos.set(0, 0);
        calcPos();
        color = rand() % 6 + 1;
    }
    cBlock(cCoordinate start)
    {
        type = rand() % 7 + 1;
        dir = rand() % 4 + 1;
        startPos = start;
        calcPos();
        color = rand() % 6 + 1;
    }

    void calcPos()
    {
        switch ((type - 1) * 4 + dir)
        {
        //All rotate should be clockwise
        case 1: case 3: //xxxx
            pos[0].set(0,0); pos[1].set(1,0); pos[2].set(2,0); pos[3].set(3,0);
            width = 4; length = 1; break;
        case 2: case 4: //x.x.x.x
            pos[0].set(0,0); pos[1].set(0,1); pos[2].set(0,2); pos[3].set(0,3);
            width = 1; length = 4; break;

        case 5: //xo.xo.xx
            pos[0].set(0,0); pos[1].set(0,1); pos[2].set(0,2); pos[3].set(1,2);
            width = 2; length = 3; break;
        case 6: //xxx.xoo
            pos[0].set(0,0); pos[1].set(1,0); pos[2].set(2,0); pos[3].set(0,1);
            width = 3; length = 2; break;
        case 7: //xx.ox.ox
            pos[0].set(0,0); pos[1].set(1,0); pos[2].set(1,1); pos[3].set(1,2);
            width = 2; length = 3; break;
        case 8: //oox.xxx
            pos[0].set(2,0); pos[1].set(0,1); pos[2].set(1,1); pos[3].set(2,1);
            width = 3; length = 2; break;

        case 9: //ox.ox.xx
            pos[0].set(1,0); pos[1].set(1,1); pos[2].set(0,2); pos[3].set(1,2);
            width = 2; length = 3; break;
        case 10: //xxx.oox
            pos[0].set(0,0); pos[1].set(1,0); pos[2].set(2,0); pos[3].set(2,1);
            width = 3; length = 2; break;
        case 11: //xx.xo.xo
            pos[0].set(0,0); pos[1].set(1,0); pos[2].set(0,1); pos[3].set(0,2);
            width = 2; length = 3; break;
        case 12: //xoo.xxx
            pos[0].set(0,0); pos[1].set(0,1); pos[2].set(1,1); pos[3].set(2,1);
            width = 3; length = 2; break;

        case 13: case 14: case 15: case 16: //xx.xx
            pos[0].set(0,0); pos[1].set(0,1); pos[2].set(1,0); pos[3].set(1,1);
            width = 2; length = 2; break;

        case 17: //oxo.xxx
            pos[0].set(1,0); pos[1].set(0,1); pos[2].set(1,1); pos[3].set(2,1);
            width = 3; length = 2; break;
        case 18: //xo.xx.xo
            pos[0].set(0,0); pos[1].set(0,1); pos[2].set(1,1); pos[3].set(0,2);
            width = 2; length = 3; break;
        case 19: //xxx.oxo
            pos[0].set(0,0); pos[1].set(1,0); pos[2].set(2,0); pos[3].set(1,1);
            width = 3; length = 2; break;
        case 20: //ox.xx.ox
            pos[0].set(1,0); pos[1].set(0,1); pos[2].set(1,1); pos[3].set(1,2);
            width = 2; length = 3; break;

        case 21: case 23: //xxo.oxx
            pos[0].set(0,0); pos[1].set(1,0); pos[2].set(1,1); pos[3].set(2,1);
            width = 3; length = 2; break;
        case 22: case 24: //ox.xx.xo
            pos[0].set(1,0); pos[1].set(0,1); pos[2].set(1,1); pos[3].set(0,2);
            width = 2; length = 3; break;

        case 25: case 27: //oxx.xxo
            pos[0].set(1,0); pos[1].set(2,0); pos[2].set(0,1); pos[3].set(1,1);
            width = 3; length = 2; break;
        case 26: case 28: //xo.xx.ox
            pos[0].set(0,0); pos[1].set(0,1); pos[2].set(1,1); pos[3].set(1,2);
            width = 2; length = 3; break;
        }
        for (int i = 0; i <= 3; i++)
            pos[i] += startPos;
    }
    void rotate()
    {
        if (dir == 4)
            dir = 1;
        else
            dir++;
        calcPos();
    }
    cCoordinate getPos(int index = -1)
    {
        if (index == -1)
            return startPos;
        return pos[index];
    }
    int getType() { return type; }
    int getDir() { return dir; }
    inline int getWidth() { return width; }
    inline int getLength() { return length; }
    inline int getColor() { return color; }
    void setPos(cCoordinate c)
    {
        startPos = c;
        calcPos();
    }

    friend bool operator==(cCoordinate coordinate, cBlock block)
    {
        return (coordinate == block.pos[0] ||
                coordinate == block.pos[1] ||
                coordinate == block.pos[2] ||
                coordinate == block.pos[3]);
    }
    friend bool operator==(cBlock block, cCoordinate coordinate)
    {
        return coordinate == block;
    }

};
#endif // CBLOCK_H
