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


    Side OppSide();
    void doAMove(Move *move, int player);
    Move* findMove();
    Move* findMoveHeuristic();
    Move* findMoveMinimax();
    int evaluateMove(Move move, Board testboard);
    int heuristicChange(Move move, int val);
    int findWorst(Move move);

    
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
