//Julia was here!

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
    side = side;
    board = Board();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            contents[i][j] = 0;}}
    if (side == BLACK) {
        contents[3][3] = -1;
        contents[4][4] = -1;
        contents[3][4] = 1;
        contents[4][3] = 1;}
    else {
        contents[3][3] = 1;
        contents[4][4] = 1;
        contents[3][4] = -1;
        contents[4][3] = -1;}
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

Side Player::OppSide() {
    if (side == BLACK) {return WHITE;}
    else {return BLACK;}}

/*void Player::doAMove(Move *move, int player) {
    int x = move->x;
    int y = move->y;
    board.set(OppSide(), x, y);
    contents[x][y] = player; //player is one for self, -1 for opponent
    int i = 1;
    while (y + i < 8) {
        if (contents[xval][yval + i] == -player) {i++;}
        else {if (i == 1) {break;}
              else {
                  for (int j = 1; j < i; j++) {
                      board.set(OppSide(), x, y + j);
                      contents[x][y + j] = player;}
                  break;}
        }
    }
    while (y - i > 0) {
        if (contents[x][y - i] == -player) {i++;}
        else {if (i == 1) {break;}
              else {
                  for (int j = 1; j < i; j++) {
                      board.set(OppSide(), x, y - j);
                      contents[x][y - j] = player;}
                  break;}
        }
    }
    while (x + i < 8) {
        if (contents[x + i][y] == -player) {i++;}
        else {if (i == 1) {break;}
              else {
                  for (int j = 1; j < i; j++) {
                      board.set(OppSide(), x + j, y);
                      contents[x + j][y] = player;}
                  break;}
        }
    }
    while (x - i > 0) {
        if (contents[x - i][y] == -player) {i++;}
        else {if (i == 1) {break;}
              else {
                  for (int j = 1; j < i; j++) {
                      board.set(OppSide(), x - j, y);
                      contents[x - j][y] = player;}
                  break;}
        }
    }
    while ((x + i < 8) && (y + i < 8)) {
        if (contents[x + i][y + i] == -player) {i++;}
        else {if (i == 1) {break;}
              else {
                  for (int j = 1; j < i; j++) {
                      board.set(OppSide(), x + j, y + j);
                      contents[x + j][y + j] = player;}
                  break;}
        }
    }
    while ((x + i < 8) && (y - i > 0)) {
        if (contents[x + i][y - i] == -player) {i++;}
        else {if (i == 1) {break;}
              else {
                  for (int j = 1; j < i; j++) {
                      board.set(OppSide(), x + j, y - j);
                      contents[x + j][y - j] = player;}
                  break;}
        }
    }
    while ((x - i > 0) && (y + i < 8)) {
        if (contents[x - i][y + i] == -player) {i++;}
        else {if (i == 1) {break;}
              else {
                  for (int j = 1; j < i; j++) {
                      board.set(OppSide(), x - j, y + j);
                      contents[x - j][y + j] = player;}
                  break;}
        }
    }
    while ((x - i > 0) && (y - i > 0) {
        if (contents[x - i][y - i] == -player) {i++;}
        else {if (i == 1) {break;}
              else {
                  for (int j = 1; j < i; j++) {
                      board.set(OppSide(), x - j, y - j);
                      contents[x - j][y - j] = player;}
                  break;}
        }
    }
}*/

Move* Player::findMove() {
if (board.hasMoves(side)) {
Move temp = Move(0, 0);
Move* move = &temp;
for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
        *move = Move(i, j);
        std::cerr << move->x << move->y << endl;
        if (board.checkMove(move, side)) {return move;}}}}
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
