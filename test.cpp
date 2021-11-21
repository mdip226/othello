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
using namespace std;

#define AI 0
#define OPPONENT 1

int main(int argc, char const *argv[])
{
    /* code */
    cout << "hi" << endl;
    // u64 white = 0x1f3f010301000000;
    // u64 black = 0x20001e1c18040000;
    u64 black = 0x001254386e385400;
    u64 white = 0x1180000081000092;
    print_uint(black);
    print_uint(white);
    print_board(black, white);
    u64 move = col_row_to_bit('d',5);
    print_uint(move);
    tuple<u64, u64> board = make_tuple(white, black);
    board = play(move, white, black, false);
    print_board(std::get<OPPONENT>(board),std::get<AI>(board));

    // tuple<u64, u64> boardBlack = make_tuple(black, white);
    // print_legal_moves(black, white, true);
    // print_legal_moves(black, white, false);
    // // print_uint(0x8000000000000000);

    return 0;
}
