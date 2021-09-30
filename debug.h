#if !defined(DEBUG_H)
#define DEBUG_H

#include <cstdint>
#include "utils.h"

void print_board(u64 black, u64 white);
void print_legal_moves(u64 black, u64 white, bool isBlack);
void print_uint(u64 bits);

#endif // DEBUG_H

