#include <cstdint>
#include "utils.h"

double timeAllocation[] = {0.015, 0.015, 0.015, 0.015, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025,
                                    0.048,  0.048, 0.048, 0.048, 0.048, 0.048, 0.050, 0.051, 0.052, 0.053,
                                    0.044,  0.045, 0.049, 0.049, 0.049, 0.051, 0.053, 0.055, 0.057, 0.059,
                                    0.060, 0.060, 0.061, 0.062, 0.063, 0.064, 0.065, 0.065, 0.065, 0.065,
                                    0.167, 0.168, 0.169, 0.169, 0.171, 0.172, 0.173, 0.175, 0.180, 0.180,
                                    0.181, 0.187, 0.196, 0.199, 0.220, 0.220, 0.220, 0.220, 0.220, 0.220,
                                    0.220, 0.250, 0.250, 0.250, 0.250, 0.250, 0.250, 0.250, 0.250, 0.250
                                  };

int moveNumber = 0;
bool timeUp = false;
int timeRemaining = 600;
int moveTime = 0;

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