#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
#include <vector>
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Side side;
    Board board;


    Side OppSide(Side side);
    void doAMove(Move *move, int player);
    Move* findMove();
    vector<Move*> findMoves(Board temp);
    Move* findMoveHeuristic();
    Move* findMoveMinimax();
    int evaluateMove(Move move, Board testboard);
    int heuristicChange(Move move, int val);
    int findWorst(Move move, Board test);
    int negascout(Board tempboard, int depth, int a, int b, int color, Side side);

    
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
