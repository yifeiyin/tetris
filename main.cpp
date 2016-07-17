/***************************************
 * Tetris Vision 1.2
 * By Yifei Yin
 * March 9, 2016
 ***************************************/

/************<TODO LIST>****************
 *
 * ~ Fix: One more type of block
 * ~ Fix: Add function Drop()
 * ~ Fix: Move in the wall by moving left/right
 * ~ Fix: Rotate into right wall
 * ~ Fix: Change the way to control
 * 5 Fix: Show the score and next block
 *
 *
 * 1 Improve: Change the position of new block
 * 2 Improve: Function rand() is not fully random
 * 3 Improve: Add speed up system
 * ~ Improve: Show the final position of dropping block
 * 5 Improve: Add Pause/Continue/Restart systems
 * 6 Improve: Refresh UI smartly
 * 7 Improve: Cheat system
 *
 *************************************/

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
#include <string>
#include "colorful.h"
#include "kbhit.h"
#include "ccoordinate.h"
#include "cblock.h"

using std::cout; using std::endl;

class cGameManager
{
private:
    int width, length;
    cCoordinate newBlockPos;
    int score;
    int * psqure;
    char left, right, down, fDown, change, quit;
    std::string tipChar;
    cBlock * pblock;
    cBlock * pNextBlock;
    bool gameOver;
    std::string gameOverInfo;
    long timer, speed;
public:
    cGameManager(int iwidth, int ilength)
    {
        srand((unsigned)time(NULL));
        width = iwidth; length = ilength;
        newBlockPos.set(width / 2, 0);
        psqure = new int [width * length];
        for (int i = 0; i <= width * length - 1; i++)
            *(psqure + i) = 0;
        score = 0;
        gameOver = false;
        gameOverInfo = "Nothing";
        left = 'a'; right = 'd'; down = 's'; fDown = ' '; change = 'w'; quit = 'q';
        tipChar = "";
        pblock = new cBlock(newBlockPos);
        pNextBlock = new cBlock(newBlockPos);
        timer = getClock(); speed = 120;
    }
    ~cGameManager()
    {
        delete pblock;
        delete pNextBlock;
        delete [] psqure;
    }
    void Draw()
    {
        cCoordinate ocd;

        system("clear");

        for (int i = 1; i <= width + 2 + 6; i++)
            cout << COLORFUL::bBLACK << "  " << COLORFUL::RESET; //first row walls
        cout << endl;

        for (int oy = 0; oy <= length - 1; oy++)
        {
            cout << COLORFUL::bBLACK << "  " << COLORFUL::RESET; //first wall of each line
            for(int ox = 0; ox <= width - 1; ox++)
            {
                ocd.set(ox, oy);

                if (ocd == *pblock) //dropping block
                {
                    switch (pblock->getColor())
                    {
                    case 1: cout << "\e[41m"; break;
                    case 2: cout << "\e[42m"; break;
                    case 3: cout << "\e[43m"; break;
                    case 4: cout << "\e[44m"; break;
                    case 5: cout << "\e[45m"; break;
                    case 6: cout << "\e[46m"; break;
                    case 7: cout << "\e[47m"; break;
                    }

                    cout << "  " << COLORFUL::RESET;
                }

                else if (ocd == finalPos(pblock))
                {
                    cout << COLORFUL::bGRAY << tipChar << COLORFUL::RESET;
                }
                else
                {
                    switch (*(psqure + oy * width + ox))
                    {
                    case 0: cout << COLORFUL::bGRAY; break;
                    case 1: cout << "\e[41m"; break;
                    case 2: cout << "\e[42m"; break;
                    case 3: cout << "\e[43m"; break;
                    case 4: cout << "\e[44m"; break;
                    case 5: cout << "\e[45m"; break;
                    case 6: cout << "\e[46m"; break;
                    case 7: cout << "\e[47m"; break;
                    default: cout << COLORFUL::bBLACK; break;
                    }
                    cout << "  " << COLORFUL::RESET;
                }
            }
            cout << COLORFUL::bBLACK << "  " << COLORFUL::bGRAY; //end wall of each line

//            if (ocd.getY() == length - 6)
//                cout << "type:" << std::setw(12-strlen("type:")) << pblock->getType() << COLORFUL::bBLACK << "  " << COLORFUL::RESET;

//            else if (ocd.getY() == length - 5)
//                cout << "dir:" << std::setw(12-strlen("dir:")) << pblock->getDir() << COLORFUL::bBLACK << "  " << COLORFUL::RESET;

//            else if (ocd.getY() == length - 4)
//                cout << "(N)type:" << std::setw(12-strlen("(N)type:")) << pNextBlock->getType() << COLORFUL::bBLACK << "  " << COLORFUL::RESET;

//            else if (ocd.getY() == length - 3)
//                cout << "(N)dir:" << std::setw(12-strlen("(N)dir:")) << pNextBlock->getDir() << COLORFUL::bBLACK << "  " << COLORFUL::RESET;

            if (ocd.getY() == length - 2)
                cout << "score:" << std::setw(10-strlen("score:")) << score << COLORFUL::bBLACK << "  " << COLORFUL::RESET;

            else if (ocd.getY() == length - 1)
                cout << "Overall:" << std::setw(10-strlen("Overall:")) << ((width-length*0.4)<0?:width-length*0.4)*(tipChar=="  "?2:1)*score << COLORFUL::bBLACK << "  " << COLORFUL::RESET;

            else
                cout << COLORFUL::bGRAY << "          " << COLORFUL::bBLACK << "  " << COLORFUL::RESET;

            cout << endl;
        }

        for (int i = 1; i <= width + 2 + 6; i++)
            cout << COLORFUL::bBLACK << "  " << COLORFUL::RESET;

        cout << endl;
    }

    void Input()
    {
        if (kbhit() == 1)
        {
            char ch = std::cin.get();
            if (ch == left)
            {
                cBlock temp = *pblock;
                temp.setPos(temp.getPos() + cCoordinate(-1, 0));
                if (pblock->getPos().getX() > 0 &&
                        !bHitGround(&temp))
                    pblock->setPos(pblock->getPos() + cCoordinate(-1, 0));
            }
            else if (ch == right)
            {
                cBlock temp = *pblock;
                temp.setPos(temp.getPos() + cCoordinate(+1, 0));
                if (pblock->getPos().getX() + pblock->getWidth() < width &&
                        !bHitGround(&temp))
                    pblock->setPos(pblock->getPos() + cCoordinate(+1, 0));
            }
            else if (ch == change)
            {
                cBlock temp = *pblock;
                temp.rotate();
                if (bHitGround(&temp) == false)
                    pblock->rotate();
            }
            else if (ch == quit)
            {gameOver = true; gameOverInfo = "KeyQ pushed";}
            else if (ch == down)
                Drop(true);
            else if (ch == fDown)
            {
                *pblock = finalPos(pblock);
                hitGround();
            }
        }
    }

    void Logic()
    {
        hitGround();
        Drop();
        hitGround();
        clearUp();
    }

    void Drop(bool force = false)
    {
        if ((getClock() >= timer + speed) || force)
        {
            pblock->setPos(pblock->getPos() + cCoordinate(0, +1));
            timer = getClock();
        }
    }

    void hitGround()
    {
        if (bHitGround(pblock))
        {
            for (int i = 0; i <= 3; i++)
                *(psqure + pblock->getPos(i).getX() +
                        pblock->getPos(i).getY() * width) = pblock->getColor();
            *pblock = *pNextBlock;
            *pNextBlock = cBlock(newBlockPos);
            if (bHitGround(pblock) == true)
            {
                Draw(); //The purpose is show the final result to user
                gameOver = true;
                gameOverInfo = "Full";
            }
        }
    }

    bool bHitGround(cBlock * pbl)
    {
        bool exp = false;
        for(int i = 0; i <= 3; i++)
            exp = ((*(psqure + (pbl->getPos(i).getY() + 1) * width + pbl->getPos(i).getX()) != 0) || //Next row of this block
                   (*(psqure + (pbl->getPos(i).getY()) * width + pbl->getPos(i).getX()) != 0) || //This row of this block
                   exp);
        exp = ((pbl->getPos().getY() + pbl->getLength() - 1 + 1) >= length ||
                pbl->getPos().getX() < 0 ||
                (pbl->getPos().getX() + pbl->getWidth() - 1 + 1) > width ||
                exp);
        return exp;
    }

    void clearUp()
    {
        int counter;

        for (int len = 1; len <= length; len++)
        {
            counter = width;
            for (int wid = 1; wid <= width; wid++)
                if (*(psqure + wid - 1 + (len - 1) * width) != 0)
                    counter--;
            if (counter == 0)
            {
                score++;
                int tempcolor = 0;
                for (int wid = 0; wid < width; wid++)
                {
                    *(psqure + wid + (len - 1) * width) = tempcolor;
                    Draw();
                    system("sleep 0.01");
                }
                for (int ilen = len - 1; ilen >= 1; ilen--)
                    for (int iwid = 0; iwid < width; iwid++)
                        if (ilen != 1)
                            *(psqure + iwid + (ilen) * width) = *(psqure + iwid + (ilen - 1) * width);
                        else
                            *(psqure + iwid + (ilen - 1) * width) = 0;
            }
            else if (counter < 0)
            {
                gameOver = true;
                gameOverInfo = "Counter shouldn't be negative";
            }
        }
    }

    void setTipChar(std::string str)
    {
        tipChar = str;
    }

    cBlock finalPos(cBlock * pbl)
    {
        cBlock tempbl = *pbl;
        for (int i = 0; i <= length; i++)
        {
            tempbl.setPos(pbl->getPos() + cCoordinate(0,i));
            if (bHitGround(&tempbl) == true)
                return tempbl;
        }
        return cBlock();
    }

    inline long getClock()
    {
        return (long)(clock() / 100);
    }

    void Run()
    {
        srand((unsigned)time(NULL));

        while (!gameOver)
        {
            Draw();
            Input();
            Logic();
            system("sleep 0.05");

        }
        cout << gameOverInfo << endl;
    }
};

int main()
{
    int wid, len;
    system("clear");
    cout << "Welcome to Tetris V1.2!\nMade by Yifei Y.\n\n"
            "Width?\n> ";
    std::cin >> wid;
    cout << "Length?\n> ";
    std::cin >> len;
    cout << "Do you want to have prompt of block? [Y/N]\n> ";
    char ch;
    std::string str;
    std::cin >> ch;
    switch (ch)
    {
    case 'Y': case 'y':
        str = "::";
        break;
    case 'N': case 'n':
        str = "  ";
        break;
    default:
        str = "::";
    }

    std::cin.clear();
    cout << "Starting . . .\n";
    system("sleep 1");
    system("clear");
    cGameManager game(wid, len);
    game.setTipChar(str);
    game.Run();

    return 0;
}
