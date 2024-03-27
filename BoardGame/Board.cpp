#include <iostream>
#include "Board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

using namespace std;

Board::Board(): Board(7,'#','*','X')
{
    //ctor
}


Board::Board(int size,char symbol1, char symbol2, char symbolRemoved)
{
    this->size= size;
    this->symbol1= symbol1;
    this->symbol2= symbol2;
    this->symbolRemoved=symbolRemoved;

    board= new char*[size];

    for(int i=0; i<size; i++)
    {

        board[i]= new char[size];
    }

    clearBoard();

    markPlayer1Symbol('a',3);
    markPlayer2Symbol('g',3);

    player1Location.c='a';
    player1Location.j=3;

    player2Location.c='g';
    player2Location.j=3;
}


Board::Board(Board& b)
{

    size = b.getSize();
    symbol1= b.symbol1;
    symbol2= b.symbol2;
    symbolRemoved= b.symbolRemoved;
    player1Location=b.player1Location;
    player2Location=b.player2Location;


    board= new char*[size];

    for(int i=0; i<size; i++)
    {

        board[i]= new char[size];


        for(int j=0; j<size; j++)
        {

            board[i][j]= b.board[i][j];
        }

    }




}
void Board::operator=(Board& b)
{
    size = b.getSize();
    symbol1= b.symbol1;
    symbol2= b.symbol2;
    symbolRemoved= b.symbolRemoved;
    player1Location=b.player1Location;
    player2Location=b.player2Location;

    deleteBoard();

    board= new char*[size];

    for(int i=0; i<size; i++)
    {

        board[i]= new char[size];


        for(int j=0; j<size; j++)
        {

            board[i][j]= b.board[i][j];
        }

    }

}

Board::~Board()
{
    deleteBoard();


}

Location Board::getPlayer1Location()
{

    return player1Location;
}



Location Board::getPlayer2Location()
{

    return player2Location;
}




void Board::deleteBoard()
{

    for(int i=0; i<size; i++)
    {

        delete[] board[i];
    }

    delete[] board;

    board=NULL;


}


int Board::getSize()
{
    return size;
}

void Board::printBoard()
{
    // top
    printf("Player 1 AI Symbol : %c \n", symbol1);
    printf("Player 2    Symbol : %c \n", symbol2);
    printf("\n");

    printf("  ");
    for(int i=0; i<size; i++)
    {

        printf(" %d  ",(i+1));
    }
    printf("\n");

    printf("  ");
    for(int i=0; i<size; i++)
    {

        printf("--- ");
    }
    printf("\n");

    // inside
    for(int i=0; i<size; i++)
    {
        printf("%c|",97+i);
        for(int j=0; j<size; j++)
        {

            printf(" %c |", board[i][j]);
        }
        printf("\n");


        printf(" |");
        for(int j=0; j<size; j++)
        {

            printf("---|", board[i][j]);
        }
        printf("\n");


    }


}

void Board::clearBoard()
{
    for(int i=0; i<size; i++)
    {

        for(int j=0; j<size; j++)
        {

            board[i][j]=' ';
        }

    }

}


void Board::markPlayer1Symbol(char c, int j)
{
    c=tolower(c);

    if( !isValidLocation(c,j))
    {
        throw string("markPlayer1Symbol : invalid location!");
    }

    int i= c-97;

    board[i][j]= symbol1;
}

void Board::markPlayer2Symbol(char c, int j)
{
    c=tolower(c);

    if( !isValidLocation(c,j))
    {
        throw string("markPlayer2Symbol: invalid location!");
    }

    int i= c-97;
    board[i][j]= symbol2;
}


bool Board::markAsRemoved(char c, int j)
{

    c=tolower(c);

    if( !isValidLocation(c,j))
    {
        throw string("markAsRemoved: invalid location!");
    }

    int i= c-97;
    board[i][j]= symbolRemoved;
    return true;
}

void Board::removeSymbol(char c, int j)
{
    c=tolower(c);

    if( !isValidLocation(c,j))
    {
        throw string("removeSymbol: invalid location!");
    }

    int i= c-97;

    board[i][j]= ' ';
}


void Board::markPlayerSymbol(char c, int j, int playerno)
{
    c=tolower(c);

    if( !isValidLocation(c,j))
    {
        throw string("markPlayerSymbol: invalid location!");
    }

    if( playerno<1 || playerno>2)
    {
        throw string("markPlayerSymbol: invalid playerno!");
    }

    int i= c-97;

    if( playerno==1)
    {
        board[i][j]= symbol1;
    }
    else if( playerno==2)
    {
        board[i][j]= symbol2;
    }
}


void Board::fillRandom()
{
    int c;
    for(int i=0; i<size; i++)
    {

        for(int j=0; j<size; j++)
        {
            c= rand()%2;
            board[i][j]= c==0 ? symbol1 : symbol2;
        }


    }



}

bool Board::isValidLocation(char c, int j)
{

    if( c<'a' || c>'g')
    {
        return false;
    }

    if( j<0 || j>size-1)
    {
        return false;
    }


    return true;

}


bool Board::isEmpty(char c, int j)
{
    int i=c-97;

    return board[i][j]==' ';

}

bool Board::hasMove(Location loc)
{
    int i=loc.c-97;
    int j=loc.j;
    if( j-1>=0 && board[i][j-1]==' ') // check left
    {
        return true;

    }
    else if( j-1>=0 && i-1>=0 && board[i-1][j-1]==' ') // check up left
    {
        return true;

    }
    else if( i-1>=0 && board[i-1][j]==' ') // check up
    {
        return true;

    }
    else if( i-1>=0 && j+1<size && board[i-1][j+1]==' ') // check up right
    {
        return true;

    }
    else if( j+1<size && board[i][j+1]==' ') // check right
    {
        return true;

    }
    else if( i+1<size &&  j+1<size &&  board[i+1][j+1]==' ') // check down right
    {
        return true;

    }
    else if( i+1<size && board[i+1][j]==' ') // check down
    {
        return true;

    }
    else if( i+1<size && j-1>=0 &&  board[i+1][j-1]==' ') // check down left
    {
        return true;

    }

    return false;
}
void Board::emptyNeighbors(Location loc, Location* locations)
{
    int i=loc.c-97;
    int j=loc.j;

    for(int k=0; k<8; k++)
    {
        locations[k].c=-1;
        locations[k].j=-1;
    }

    if( j-1>=0 && board[i][j-1]==' ') // check left
    {

        locations[0]= {loc.c, loc.j-1};

    }


    if( j-1>=0 && i-1>=0 && board[i-1][j-1]==' ') // check up left
    {
        locations[1]= {static_cast<char>(loc.c-1), loc.j-1};

    }

    if( i-1>=0 && board[i-1][j]==' ') // check up
    {
        locations[2]= {static_cast<char>(loc.c-1), loc.j};

    }

    if( i-1>=0 && j+1<size && board[i-1][j+1]==' ') // check up right
    {
        locations[3]= {static_cast<char>(loc.c-1), loc.j+1};

    }

    if( j+1<size && board[i][j+1]==' ') // check right
    {
        locations[4]= {loc.c, loc.j+1};

    }

    if( i+1<size &&  j+1<size &&  board[i+1][j+1]==' ') // check down right
    {
        locations[5]= {static_cast<char>(loc.c+1), loc.j+1};

    }

    if( i+1<size && board[i+1][j]==' ') // check down
    {
        locations[6]= {static_cast<char>(loc.c+1), loc.j};

    }

    if( i+1<size && j-1>=0 &&  board[i+1][j-1]==' ') // check down left
    {
        locations[7]= {static_cast<char>(loc.c+1), loc.j-1};

    }

}
bool Board::movePlayer1(Location loc)
{
    return movePlayer1(loc.c, loc.j);
}
bool Board::movePlayer2(Location loc)
{
    return movePlayer2(loc.c, loc.j);


}


bool Board::movePlayer1(char c, int j)
{
    int i= player1Location.c-97;

    board[i][player1Location.j]=' ';

    i= c-97;
    board[i][j]=symbol1;

    player1Location.c= c;
    player1Location.j= j;

    return true;
}
bool Board::movePlayer2(char c, int j)
{
    int i= player2Location.c-97;
    board[i][player2Location.j]=' ';

    i=c-97;
    board[i][j]=symbol2;

    player2Location.c= c;
    player2Location.j= j;

    return true;
}

bool Board::isValidMove(Location s, Location t)
{
    if ( !isValidLocation(s.c,s.j) || !isValidLocation(t.c,t.j) )
    {
        cout <<" not valid" <<endl;
        return false;
    }
    Location* moveLocations= new Location[8] {{-1,-1}};
    emptyNeighbors(s, moveLocations);
    for( int j=0; j<8; j++)
    {

        if( moveLocations[j].c==t.c && moveLocations[j].j==t.j)
        {
            delete[] moveLocations;
            return true;
        }
    }
    delete[] moveLocations;
    return false;
}

