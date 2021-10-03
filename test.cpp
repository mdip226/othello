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
    u64 white = 0x1f3f010301000000;
    u64 black = 0x20001e1c18040000;
    tuple<u64, u64> boardBlack = make_tuple(black, white);
    tuple<u64, u64> boardWhite = make_tuple(white, black);
    print_board(black, white);
    print_legal_moves(black, white, true);
    print_legal_moves(black, white, false);
    // print_uint(0x8000000000000000);

    return 0;
}
