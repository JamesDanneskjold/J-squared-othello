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

//*****************Julia Additions*****************
    int contents[8][8];
    Side OppSide();
    void doAMove(Move *move, int player);
    Move* findMove();
    vector<Move*> findMoves();
    int evaluateMove(Move move);
//*************************************************
    
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
