#if !defined(ACTIONS_H)
#define ACTIONS_H

#include <cstdint>

uint64_t make_move(uint64_t move, uint64_t board);
uint64_t row_col_to_bit(char col, int row);
uint64_t init_black();
uint64_t init_white();

#endif // ACTIONS_H

