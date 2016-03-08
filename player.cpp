//Julia was here!
//Here is a trivial change!
#include "player.h"

/*
 * This is a comment added by James for the initial section of the
 * program.
 */

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    this->side = side;
    Board board = Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

Side Player::OppSide() {
    if (side == BLACK) {return WHITE;}
    else {return BLACK;}}

Move* Player::findMove() 
{
    if (board.hasMoves(side)) 
    {
        Move *move = new Move(0, 0);
        for (int i = 0; i < 8; i++) 
        {
            for (int j = 0; j < 8; j++)
            {
                *move = Move(i, j);
                 if (board.checkMove(move, side)) 
                 {
                     return move;
                 }
            }
       }
    }
    return NULL;
}

//vector<Move*> Player::findMoves() {}

//int Player::evaluateMove(Move move) {}


/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    //doAMove(opponentsMove, -1);
    board.doMove(opponentsMove, OppSide());
    Move* move = findMove();
    //doAMove(move, 1);
    board.doMove(move, side);
    return move;
}
