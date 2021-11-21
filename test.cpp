#include <iostream>
#include <sstream>
#include <string>
#include <cstdint>
#include <bitset>
#include <tuple>
#include "debug.h"
#include "moves.h"
#include "actions.h"
#include "utils.h"
#include "minmax.h"

#define AI 0
#define OPPONENT 1

int main(int argc, char const *argv[])
{
    u64 white = init_white();
    u64 black = init_black();
    std::tuple<u64, u64> board = std::make_tuple(black, white);
    print_board(black, white);
    playAlphaBeta(board);
    return 0;
}
