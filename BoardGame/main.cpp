#include <iostream>
#include "Board.h"
#include "Game.h"
#include <time.h>

using namespace std;

int main()
{

    srand(time(NULL));

    Game game;
    game.run();



    return 0;
}

void test1()
{
     try
    {
        //srand(1);

        Board b;

        //b.fillRandom();
        b.markPlayer1Symbol('g',4);
        b.markPlayer2Symbol('A',4);
        b.printBoard();


    }
    catch(string& exp)
    {

        cout << exp<< endl;
    }

}

