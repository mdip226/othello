#if !defined(MOVES_H)
#define MOVES_H

#include <cstdint>

uint64_t get_legal_moves(uint64_t player, uint64_t opponent);

int bitCount(uint64_t bits);

uint64_t pick_randomly(uint64_t moves);

#endif // MOVES_H

