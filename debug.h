#if !defined(DEBUG_H)
#define DEBUG_H

#include "utils.h"

#define DEBUG 1

// prints out board state
void print_board(u64 black, u64 white);

// prints legal moves
// if isBlack == true, prints black moves
// if isBlack == false, prints white moves
void print_legal_moves(u64 black, u64 white, bool isBlack);

// prints a single u64 like it were a board
void print_uint(u64 bits);

#endif // DEBUG_H

