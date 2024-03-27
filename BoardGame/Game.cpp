#include <iostream>
#include "Game.h"

using namespace std;

Game::Game()
{
    board= new Board();
}

Game::~Game()
{
    delete board;
}



void Game::run2()
{
    char p2c;
    int p2j;

    Location player2Location= {-1,-1};
    Location player2RemoveLocation= {-1,-1};
    bool gameover=false;

    board->printBoard();

    while(true)
    {

        int bestValue = -1;
        Board b(*board);

        Location* moveLocations= new Location[8] {{-1,-1}};
        Location* removeLocations= new Location[8] {{-1,-1}};
        Location nextmove= {-1,-1};
        Location nextremove= {-1,-1};

        Location player1LocationOld= {-1,-1};

        bool hasmove=false;

        cout << "Player Locations Player 1 :  "  << board->getPlayer1Location().c << board->getPlayer1Location().j+1  << "   Player 2 : " << board->getPlayer2Location().c << board->getPlayer2Location().j+1 << endl;

        cout <<"-------------------------------------------------------------------"<<endl;
        cout<< "Player 1 turn" <<endl;

        cout <<endl;

        player1LocationOld= b.getPlayer1Location();



        b.emptyNeighbors(b.getPlayer1Location(),moveLocations);


        for(int i=0; i<8; i++)
        {

            if( moveLocations[i].c!=-1 && moveLocations[i].j!=-1)
            {

                hasmove=true;

                b.movePlayer1(moveLocations[i]);
                b.emptyNeighbors(b.getPlayer2Location(), removeLocations);

                for( int j=0; j<8; j++)
                {
                    if( removeLocations[j].c!=-1 && removeLocations[j].j!=-1)
                    {
                        b.markAsRemoved(removeLocations[j].c,removeLocations[j].j);

                        int v = minimax(b, 0, 2);
                        cout <<" move " << i <<" " << j<< "  depth : " << endl;
                        if( v> bestValue)
                        {
                            bestValue=v;
                            nextmove= moveLocations[i];
                            nextremove= removeLocations[j];

                        }

                        b.removeSymbol(removeLocations[j].c,removeLocations[j].j);

                    }

                }


                b.movePlayer1(player1LocationOld);

            }

        }

        if( hasmove) // for player1
        {

            board->movePlayer1(nextmove);
            board->markAsRemoved(nextremove.c,nextremove.j);

            cout << "Player 1 move   : " << nextmove.c << nextmove.j+1 <<endl;
            cout << "Player 1 remove : " << nextremove.c << nextremove.j+1 <<endl;
            cout <<endl;
            board->printBoard();

            cout << "Player Locations Player 1 :  "  << board->getPlayer1Location().c << board->getPlayer1Location().j+1  << "   Player 2 : " << board->getPlayer2Location().c << board->getPlayer2Location().j+1 << endl;
        }
        else
        {
            cout <<"Player 1 has been lost" <<endl;
            break;
        }


        if( board->hasMove( board->getPlayer2Location()))
        {
            cout <<"Player 2 turn" <<endl;
            cout << "Enter move location   :" ;
            cin>> p2c >> p2j;

            player2Location.c= p2c;
            player2Location.j = p2j-1;

            cout << "Enter remove location :" ;
            cin>> p2c >> p2j;

            player2RemoveLocation.c= p2c;
            player2RemoveLocation.j = p2j-1;

            board->movePlayer2(player2Location);
            board->markAsRemoved(player2RemoveLocation.c,player2RemoveLocation.j);

            board->printBoard();

        }
        else
        {
            cout <<"Player 2 has been lost" <<endl;
            break;
        }

        board->printBoard();
        cout <<endl;

    }

}



void Game::run()
{
    char p2c;
    int p2j;

    Location player2Location= {-1,-1};
    Location player2RemoveLocation= {-1,-1};
    bool gameover=false;

    board->printBoard();

    while(true)
    {

        int bestValue = -1000;
        Board b(*board);

        Location* moveLocations= new Location[8] {{-1,-1}};
        Location* removeLocations= new Location[8] {{-1,-1}};
        Location nextmove= {-1,-1};
        Location nextremove= {-1,-1};

        Location player1LocationOld= {-1,-1};

        bool hasmove=false;

        cout << "Player Locations Player 1 :  "  << board->getPlayer1Location().c << board->getPlayer1Location().j+1  << "   Player 2 : " << board->getPlayer2Location().c << board->getPlayer2Location().j+1 << endl;

        cout <<"-------------------------------------------------------------------"<<endl;
        cout<< "Player 1 turn" <<endl;

        cout <<endl;

        player1LocationOld= b.getPlayer1Location();



        b.emptyNeighbors(b.getPlayer1Location(),moveLocations);


        for(int i=0; i<8; i++)
        {

            if( moveLocations[i].c!=-1 && moveLocations[i].j!=-1)
            {



                b.movePlayer1(moveLocations[i]);
                b.emptyNeighbors(b.getPlayer2Location(), removeLocations);

                for( int j=0; j<8; j++)
                {
                    if( removeLocations[j].c!=-1 && removeLocations[j].j!=-1)
                    {
                        b.markAsRemoved(removeLocations[j].c,removeLocations[j].j);

                        int v = minimax(b, 0, 2);
                        //cout <<" move " << i <<" " << j<< "  depth : " << endl;
                        if( v> bestValue)
                        {
                            hasmove=true;
                            bestValue=v;
                            nextmove= moveLocations[i];
                            nextremove= removeLocations[j];

                        }

                        b.removeSymbol(removeLocations[j].c,removeLocations[j].j);

                    }

                }


                b.movePlayer1(player1LocationOld);

            }

        }

        if( hasmove) // for player1
        {

            board->movePlayer1(nextmove);
            board->markAsRemoved(nextremove.c,nextremove.j);

            cout << "Player 1 move   : " << nextmove.c << nextmove.j+1 <<endl;
            cout << "Player 1 remove : " << nextremove.c << nextremove.j+1 <<endl;
            cout <<endl;
            board->printBoard();

            cout << "Player Locations Player 1 :  "  << board->getPlayer1Location().c << board->getPlayer1Location().j+1  << "   Player 2 : " << board->getPlayer2Location().c << board->getPlayer2Location().j+1 << endl;
        }
        else
        {
            cout <<"Player 1 has been lost" <<endl;
            break;
        }


        if( board->hasMove( board->getPlayer2Location()))
        {
            cout <<"Player 2 turn" <<endl;
            while(true)
            {
                cout << "Enter move location   :" ;
                cin>> p2c >> p2j;

                player2Location.c= p2c;
                player2Location.j = p2j-1;
                if( board->isValidMove( board->getPlayer2Location(),  player2Location) ) {
                    break;
                }
                else {
                    cout <<"Enter a valid move location!" <<endl;
                }
            }
            while(true)
            {
                cout << "Enter remove location :" ;
                cin>> p2c >> p2j;

                board->isValidLocation(p2c, p2j-1);

                player2RemoveLocation.c= p2c;
                player2RemoveLocation.j = p2j-1;
                if ( board->isValidLocation(p2c, p2j-1) && board->isEmpty(p2c,p2j-1)  )
                {
                    break;
                }
                else {
                    cout <<"Enter a valid remove location!" <<endl;
                }

            }

            board->movePlayer2(player2Location);
            board->markAsRemoved(player2RemoveLocation.c,player2RemoveLocation.j);

            board->printBoard();

        }
        else
        {
            cout <<"Player 2 has been lost" <<endl;
            break;
        }

        board->printBoard();
        cout <<endl;

    }

}

int Game::minimax(Board& board, int depth, int maximizingPlayer)
{
//    if( depth == 0)   //or node is a terminal node
//        return 1;   //the utility of the node

    int x;
   // board.printBoard();
    //cout <<" enter 0 to continue" <<endl;
    //cin>>x;

    if( maximizingPlayer==1)
    {
        if( depth==MAXDEPTH) return -1000;

        int bestValue = -1000;
        Board b(board);
        Location* moveLocations= new Location[8];
        Location* removeLocations= new Location[8];

        Location nextmove= {-1,-1};
        Location nextremove= {-1,-1};

        Location player1LocationOld= {-1,-1};
        Location removeOld= {-1,-1};
        bool hasmove=false;

        b.emptyNeighbors(b.getPlayer1Location(),moveLocations);
        player1LocationOld= b.getPlayer1Location();
        for(int i=0; i<8; i++)
        {
            if( moveLocations[i].c!=-1 && moveLocations[i].j!=-1)
            {


                b.movePlayer1(moveLocations[i]);
                b.emptyNeighbors(b.getPlayer2Location(), removeLocations);

                for( int j=0; j<8; j++)
                {
                    if( removeLocations[j].c!=-1 && removeLocations[j].j!=-1)
                    {
                        b.markAsRemoved(removeLocations[j].c,removeLocations[j].j);

                        int v = minimax(b, depth+1, 2);
                        if( v> bestValue)
                        {
                             hasmove=true;
                            bestValue=v;
                            nextmove= moveLocations[i];
                            nextremove= removeLocations[j];

                        }

                        b.removeSymbol(removeLocations[j].c,removeLocations[j].j);



                    }
                }


                b.movePlayer1(player1LocationOld);


            }


        }
        //cout <<" maximizer move " << "  depth : " << endl;
        delete[] moveLocations;
        delete[] removeLocations;

        if(!hasmove)
        {
            bestValue=1;
        }

        return bestValue;


    }
    else  // (* minimizing player *)
    {

        if( depth==MAXDEPTH) return 1000;

        int bestValue = 1000;
        Board b(board);
        Location* moveLocations= new Location[8];
        Location* removeLocations= new Location[8];

        Location nextmove= {-1,-1};
        Location nextremove= {-1,-1};

        Location player2LocationOld= {-1,-1};
        Location removeOld= {-1,-1};
        bool hasmove=false;

        b.emptyNeighbors(b.getPlayer2Location(),moveLocations);
        player2LocationOld= b.getPlayer2Location();
        for(int i=0; i<8; i++)
        {
            if( moveLocations[i].c!=-1 && moveLocations[i].j!=-1)
            {


                b.movePlayer2(moveLocations[i]);
                b.emptyNeighbors(b.getPlayer1Location(), removeLocations);

                for( int j=0; j<8; j++)
                {
                    if( removeLocations[j].c!=-1 && removeLocations[j].j!=-1)
                    {
                        b.markAsRemoved(removeLocations[j].c,removeLocations[j].j);

                        int v = minimax(b, depth+1, 1);
                        if( v < bestValue)
                        {
                            hasmove=true;
                            bestValue=v;
                            nextmove= moveLocations[i];
                            nextremove= removeLocations[j];


                        }

                        b.removeSymbol(removeLocations[j].c,removeLocations[j].j);

                    }
                }
                b.movePlayer2(player2LocationOld);


            }


        }
       // cout <<" minimizer move " << "  depth : " << depth<< endl;



        delete[] moveLocations;
        delete[] removeLocations;

        if( !hasmove)
        {
            bestValue=-1;
        }

        return bestValue;
    }
}
