#include <cstdint>
#include <tuple>
#include <iostream> //debug
#include "utils.h"
#include "debug.h"
u64 _make_move(u64 move, u64 board)
{
    return move | board;
}

std::tuple<u64, u64> play(u64 move, u64 player, u64 opponent) {
    // dont forget to check whether it is a legal move or not....

    player = _make_move(move, player);
    u64 flips_final = 0x0000000000000000;

    uint64_t full = player | opponent;
    uint64_t mask = 0b0000000000000000000000000000000000000000000000000000000000000000;
    uint64_t empty = (~full) & (~mask);
    uint64_t candidate;
    int cols = 8;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << i << std::endl;
        int shift = 1;
        if (i != 2 && i != 6)
        {
            shift = cols;
        }
        if (i == 1 || i == 5)
        {
            shift++;
        }
        if (i == 3 || i == 7)
        {
            shift--;
        }
        if (i < 4)
        {
            u64 flips = 0x0000000000000000;
            u64 scanner = move >> shift;
            // bool valid = false;
            candidate = opponent & scanner;
            // print_uint(candidate);
            while (candidate != 0UL)
            {
                std::cout << "candidate:" << std::endl;
                print_uint(candidate);
                std::cout << "board:" << std::endl;
                print_board(player, opponent);
                // std::cout << "opponent:" << std::endl;
                // print_uint(opponent);
                flips |= candidate;
                scanner >>= shift;
                if ((player & scanner) !=0UL) {
                    // valid = true;
                    flips_final |= flips;
                    break;
                }
                std::cout << "flips:" << std::endl;
                print_uint(flips);
                candidate = opponent & scanner;
            }
        }
        else
        {
            u64 flips = 0x0000000000000000;
            u64 scanner = move << shift;
            candidate = opponent & scanner;
            while (candidate != 0UL)
            {
                std::cout << "candidate:" << std::endl;
                print_uint(candidate);
                std::cout << "board:" << std::endl;
                print_board(player, opponent);
                // std::cout << "player:" << std::endl;
                // print_uint(player);
                // std::cout << "opponent:" << std::endl;
                // print_uint(opponent);
                flips |= candidate;
                std::cout << "flips:" << std::endl;
                print_uint(flips);
                scanner <<= shift;
                if ((player & scanner) != 0UL)
                {
                    flips_final |= flips;
                    break;
                }
                candidate = opponent & (move << shift);
                // std::cout << "candidate:" << std::endl;
                // print_uint(candidate);
            }
        }
        // std::cout << std::bitset<64>(moves).to_string() << std::endl;
    }

    std::cout << "flips_final:" << std::endl;
    print_uint(flips_final);
    std::cout << "opponent:" << std::endl;
    print_uint(opponent);
    opponent = (~flips_final) & opponent;
    player |= flips_final;
    print_board(player, opponent);
    return std::tie(player, opponent);
}