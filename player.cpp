//Julia was here!
//Here is a trivial change!
#include "player.h"
#include "iostream"

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

Side Player::OppSide(Side side) {
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


vector<Move*> Player::findMoves(Board temp) 
{
	vector<Move*> moves;
	Move *move = new Move(0, 0);
	for (int i = 0; i < 8; i++) 
	{
		for (int j = 0; j < 8; j++)
		{
			*move = Move(i, j);
			 if (temp.checkMove(move, side)) 
			 {
				 moves.push_back(move);
			 }
		}
	}
	return moves;
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
                    val = findWorst(move, board);
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

int Player::findWorst(Move move, Board test)
{
    Board tempboard = test;
    Move *firstmove = &move;
    tempboard.doMove(firstmove, side);
    int val, worst = tempboard.countBlack() - tempboard.countWhite();
    if (tempboard.hasMoves(OppSide(side))) 
    {
        Move move = Move(0, 0);
        for (int i = 0; i < 8; i++) 
        {
            for (int j = 0; j < 8; j++)
            {
                 move = Move(i, j);
                 if (tempboard.checkMove(&move, OppSide(side))) 
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

int Player::negascout(Board tempboard, int depth, int a, int b, int color, Side side)
{
	Board temp = tempboard;
	vector<Move*> moves;
	int score;
    if(depth == 0)
    {
        return color * (tempboard.countBlack() - tempboard.countWhite());
	}
	if(tempboard.hasMoves(side))
	{
	     moves = findMoves(tempboard);
	}
    for(unsigned int i = 0; i < moves.size(); i++)
    {
		temp = tempboard;
        if(i != 0)
        {
			temp.doMove(moves[i], side);
            score = -1 * negascout(temp, depth-1, -a-1, -a, -color, OppSide(side));
            temp = tempboard;
            if (a < score && score < b)
            {
				temp.doMove(moves[i], side);
                score = -negascout(temp, depth-1, -b, -score, -color, OppSide(side));
                temp = tempboard;
			}
		}
        else
        {
			temp.doMove(moves[i], side);
            score = -negascout(temp, depth-1, -b, -a, -color, OppSide(side));
            temp = tempboard;
		}
        a = max(a, score);
        if (a >= b)
        {
            break;
        }
	}
    return a;
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
    // This is the very naive initial AI that just picks
    // the first move it finds.
    
    /*
    board.doMove(opponentsMove, OppSide());
    Move* move = findMove();
    board.doMove(move, side);
    return move;
    */
    /*if(testingMinimax)

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
    }*/
    board.doMove(opponentsMove, OppSide(side));
    int val, best = -10000, i_best = 0, j_best = 0;
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
                    val = negascout(board, 3, -1000, 1000, 1, side);
                    if (val > best)
                    {
                        i_best = i;
                        j_best = j;
                        best = val;
                    }
                }
            }
        }
        Move* output = new Move(i_best, j_best);
        board.doMove(output, side);
        return output;
    }
    return NULL;
    
}
