#include <cstdint>
#include "utils.h"

u64 col_row_to_bit(char col, int row)
{
    u64 blank = 0b0000000000000000000000000000000000000000000000000000000000000001;
    int shift = (7 - (col - '1' - '0')) + (8 * (7 - (row - 1)));
    // cout << shift << endl;
    u64 move = blank << shift;
    // cout << bitset<64>(move).to_string() << endl;
    return move;
}

u64 init_black()
{
    u64 start = 0x0000000000000000;
    u64 black = start | col_row_to_bit('e', 4);
    black = black | col_row_to_bit('d', 5);
    return black;
}

u64 init_white()
{
    u64 start = 0x0000000000000000;
    u64 white = start | col_row_to_bit('d', 4);
    white = white | col_row_to_bit('e', 5);
    return white;
}