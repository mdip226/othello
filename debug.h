#if !defined(DEBUG_H)
#define DEBUG_H

#include <cstdint>

void print_board(uint64_t black, uint64_t white);
void print_legal_moves(uint64_t player, uint64_t opponent);
void print_uint(uint64_t bits);

#endif // DEBUG_H

