#include <iostream>
#include <sstream>
#include <string>
#include <cstdint>
#include <bitset>
#include <tuple>
#include <vector>
#include "debug.h"
#include "moves.h"
#include "actions.h"
#include "utils.h"
#include <time.h>
#include <unistd.h>
// #include "minmax.h"

#define AI 0
#define OPPONENT 1

int main(int argc, char const *argv[])
{
    std::vector<char> A;
    while (1) {
        A.push_back('A');
        std::string s(A.begin(), A.end());
        std::cout << s << std::endl;
    }
    // std::cout << ~0UL << std::endl;
    // time_t start = time(NULL);
    // std::cout << start << std::endl;
    // sleep(5);
    // time_t end = time(NULL);
    // std::cout << end << std::endl;
    // std::cout << (end-start) << std::endl;
    
    // u64 white = init_white();
    // u64 black = init_black();
    // std::tuple<u64, u64> board = std::make_tuple(black, white);
    // print_board(black, white);
    // playAlphaBeta(board);
    return 0;
}
