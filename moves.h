#if !defined(MOVES_H)
#define MOVES_H

#include <cstdint>
#include "utils.h"

u64 get_legal_moves(u64 player, u64 opponent);

int bitCount(u64 bits);

u64 pick_randomly(u64 moves);

#endif // MOVES_H

