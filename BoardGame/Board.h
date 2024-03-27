#ifndef BOARD_H
#define BOARD_H
#include "GameTypes.h"


class Board
{
    public:
        Board();
        Board(int size,char symbol1, char symbol2, char symbolRemoved);
        Board(Board& b);

        virtual ~Board();

        void operator=(Board& b);

        int getSize();
        void printBoard();
        void clearBoard();

        Location getPlayer1Location();
        Location getPlayer2Location();

        void setPlayer1Symbol(char c);
        void setPlayer2Symbol(char c);


        bool isValidLocation(char c, int j);
        void markPlayer1Symbol(char c, int j);
        void markPlayer2Symbol(char c, int j);

        bool markAsRemoved(char c, int j);

        void removeSymbol(char c, int j);

        void markPlayerSymbol(char c, int j, int playerno);

        void removePlayerSymbol(char i, int j, int playerno);

        void fillRandom();
        bool isEmpty(char c, int j);

        bool hasMove(Location loc);

        void emptyNeighbors(Location loc, Location* locations);

        bool isValidMove(Location s, Location t);

        bool movePlayer1(char c, int j);
        bool movePlayer2(char c, int j);
        bool movePlayer1(Location loc);
        bool movePlayer2(Location loc);






    protected:

    private:

        int size;
        char** board;
        char symbol1;
        char symbol2;
        char symbolRemoved;
        Location player1Location;
        Location player2Location;

        void deleteBoard();
};

#endif // BOARD_H

