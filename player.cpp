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
Player::Player(Side side) 
{
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

Move* Player::findMoveHeuristic()
{
    int val, best = -10000;
    Move result = Move(0, 0);
    if (board.hasMoves(side)) 
    {
        Move move = Move(0, 0);
        for (int i = 0; i < 8; i++) 
        {
            for (int j = 0; j < 8; j++)
            {
                 move = Move(i, j);
                 if (board.checkMove(&move, side)) 
                 {
                     val = evaluateMove(move, board);
                     val = heuristicChange(move, val);
                     if(val > best)
                     {
                         result = Move(i, j);
                         best = val;
                     }
                 }
            }
        }
    }
    else
    {
	return NULL;
    }
    Move* output = new Move(result);
    return output;
}

Move* Player::findMoveMinimax()
{
    int val, best = -10000;
    Move result = Move(0, 0);
    if (board.hasMoves(side))
    {
        Move move = Move(0, 0);
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                move = Move(i, j);
                if (board.checkMove(&move, side))
                {
                    val = findWorst(move);
                    if (val > best)
                    {
                        result = Move(i, j);
                        best = val;
                    }
                }
            }
        }
    }
    else
    {
        return NULL;
    }
    Move* output = new Move(result);
    return output;
}

int Player::evaluateMove(Move move, Board testboard)
{
    Board tempboard = testboard;
    Move *testmove = &move;
    tempboard.doMove(testmove, side);
    int val = tempboard.countBlack() - tempboard.countWhite();
    if(side == 0)
    {
        val *= -1;
    }
    return val;
}

int Player::heuristicChange(Move move, int val)
{
    if (move.getX() == 0 || move.getX() == 7)
    {
        if (move.getY() == 0 || move.getY() == 7)
        {
            val += 40;
        }
        else
        {
            val += 20;
        }
    }
    else if (move.getY() == 0 || move.getY() == 7)
    {
        val += 20;
    }
    return val;
}

int Player::findWorst(Move move)
{
    Board tempboard = board;
    Move *firstmove = &move;
    tempboard.doMove(firstmove, side);
    int val, worst = tempboard.countBlack() - tempboard.countWhite();
    if (tempboard.hasMoves(OppSide())) 
    {
        Move move = Move(0, 0);
        for (int i = 0; i < 8; i++) 
        {
            for (int j = 0; j < 8; j++)
            {
                 move = Move(i, j);
                 if (tempboard.checkMove(&move, OppSide())) 
                 {
                     val = evaluateMove(move, tempboard);
                     if(val < worst)
                     {
                         worst = val;
                     }
                 }
            }
       }
    }
    return worst;
}	
	

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
    // This is the very naive initial AI that just pick
    // the first move it finds.
    
    /*
    board.doMove(opponentsMove, OppSide());
    Move* move = findMove();
    board.doMove(move, side);
    return move;
    */

    if(testingMinimax)
    {
        board.doMove(opponentsMove, OppSide());
        Move* move = findMoveMinimax();
        board.doMove(move, side);
        return move;
    }
    else
    {	
        board.doMove(opponentsMove, OppSide());
        Move* move = findMoveHeuristic();
        board.doMove(move, side);
        return move;
    }
}
