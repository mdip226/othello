#include <cstdint>
//
// #define NORTH 0xFFFF000000000000UL
// #define EAST 0x0303030303030303UL
// #define SOUTH 0x000000000000FFFFUL
// #define WEST 0xC0C0C0C0C0C0C0C0UL

uint64_t col_row_to_bit(char col, int row)
{
    uint64_t blank = 0b0000000000000000000000000000000000000000000000000000000000000001;
    int shift = (7 - (col - '1' - '0')) + (8 * (7 - (row - 1)));
    // cout << shift << endl;
    uint64_t move = blank << shift;
    // cout << bitset<64>(move).to_string() << endl;
    return move;
}

uint64_t init_black()
{
    uint64_t start = 0x0000000000000000;
    uint64_t black = start | col_row_to_bit('e', 4);
    black = black | col_row_to_bit('d', 5);
    return black;
}

uint64_t init_white()
{
    uint64_t start = 0x0000000000000000;
    uint64_t white = start | col_row_to_bit('d', 4);
    white = white | col_row_to_bit('e', 5);
    return white;
}