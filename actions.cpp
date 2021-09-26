#include <cstdint>
#include <tuple>
#include <iostream> //debug
#include "utils.h"
#include "debug.h"
u64 _make_move(u64 move, u64 board)
{
    return move | board;
}

std::tuple<u64, u64> play(u64 move, u64 player, u64 opponent, bool isBlack) {
    // dont forget to check whether it is a legal move or not....
    // TODO: need to add & with empty spaces somewhere in algorithm!

    player = _make_move(move, player);
    u64 flips_final = 0x0000000000000000;

    u64 candidate;
    int cols = 8;
    for (int i = 0; i < 8; ++i)
    {
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
            candidate = opponent & scanner;
            while (candidate != 0UL)
            {
                flips |= candidate;
                scanner >>= shift;
                if ((player & scanner) != 0UL) {
                    flips_final |= flips;
                    break;
                }
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
                flips |= candidate;
                scanner <<= shift;
                if ((player & scanner) != 0UL)
                {
                    flips_final |= flips;
                    break;
                }
                candidate = opponent & scanner;
            }
        }
    }

    opponent = (~flips_final) & opponent;
    player |= flips_final;
    if (isBlack) {
        return std::tie(player, opponent);
    }
    else {
        return std::tie(opponent, player);
    }
}