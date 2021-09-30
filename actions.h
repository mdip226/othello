#if !defined(ACTIONS_H)
#define ACTIONS_H

#include "utils.h"

// applies a move to a board
u64 _make_move(u64 move, u64 board);

// returns a tuple in the form tuple<player, opponent>
std::tuple<u64, u64> play(u64 move, u64 player, u64 opponent, bool isBlack);

bool is_end(u64 player, u64 opponent);

#endif // ACTIONS_H

