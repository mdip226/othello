#include <tuple>
#include <iostream>
#include "utils.h"
#include "debug.h"
#include "moves.h"

u64 _make_move(u64 move, u64 board)
{
    return move | board;
}
void send_move(u64 move, bool isBlack) {
    char cols[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    int rows[] = {1, 2, 3, 4, 5, 6, 7, 8};
    char col;
    int row;
    char color = isBlack ? 'B' : 'W';
    
    u64 mask = 0x8000000000000000;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((mask & move) != 0UL) {
                std::cout << color << " " << cols[j] << " " << rows[i] << std::endl;
            }
            move <<= 1;
        }
    }
}

std::tuple<u64, u64> play(u64 move, u64 player, u64 opponent, bool isAI) {
    // dont forget to check whether it is a legal move or not....
    // TODO: need to add & with empty spaces somewhere in algorithm!
    // ACTUALLY i think we just need to check for the edge on that first adjacent piece and stop there

    player = _make_move(move, player);
    u64 flips_final = 0x0000000000000000;

    u64 candidate;
    int cols = 8;
    // when i = ... direction
    // 0 = south
    // 1 = southeast
    // 2 = east
    // 3 = southwest
    // 4 = north
    // 5 = northwest
    // 6 = west
    // 7 = northeast
    for (int i = 0; i < 8; ++i)
    { 
        if (i == 0 && (move & SOUTH2) != 0UL) {
            continue;
        }
        if (i == 1 && (move & (SOUTH2|EAST2)) != 0UL) {
            continue;
        }
        if (i == 2 && (move & EAST2) != 0UL) {
            continue;
        }
        if (i == 3 && (move & (SOUTH2|WEST2)) != 0UL) {
            continue;
        }
        if (i == 4 && (move & NORTH2) != 0UL) {
            continue;
        }
        if (i == 5 && (move & (NORTH2|WEST2)) != 0UL) {
            continue;
        }
        if (i == 6 && (move & WEST2) != 0UL) {
            continue;
        }
        if (i == 7 && (move & (NORTH2|EAST2)) != 0UL) {
            continue;
        }
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
    if (isAI) {
        return std::make_tuple(player, opponent);
    }
    else {
        return std::make_tuple(opponent, player);
    }
}

bool is_end(u64 player, u64 opponent) {
    u64 player_moves = get_legal_moves(player, opponent);
    u64 opponent_moves = get_legal_moves(opponent, player);
    // std::cout << "C is_end(): player moves, opponent moves:" << std::endl;
    // print_uint(player_moves);
    // print_uint(opponent_moves);
    return (player_moves | opponent_moves) == 0UL;
}