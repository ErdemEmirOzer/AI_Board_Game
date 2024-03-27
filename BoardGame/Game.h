#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "GameTypes.h"

class Game
{
    public:
        Game();
        virtual ~Game();
        void run();
        void run2();

        int minimax(Board& board, int depth, int maximizingPlayer);

    protected:

    private:
        Board* board;
        const int MAXDEPTH=4;
};

#endif // GAME_H

