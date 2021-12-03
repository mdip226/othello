#include <cstdint>
#include <iostream>
#include <bitset>
#include "debug.h"
#include "utils.h"


u64 get_legal_moves(u64 player, u64 opponent) {
    int shifts[] = {1,7,8,9,1,7,8,9};
    u64 dir_masks[] = {EAST,SOUTH|WEST,SOUTH,SOUTH|EAST,WEST,NORTH|EAST,NORTH,NORTH|WEST};
    u64 full = player | opponent;
    u64 mask = 0UL;
    u64 empty = (~full) & (~mask);
    u64 moves = 0UL;
    u64 candidates;
    for (int i = 0; i < 8; ++i)
    {
        // std::cout << "C " << i << std::endl;
        // std::cout << "C player:" << std::endl;
        // print_uint(player);
        // std::cout << "C opponent:" << std::endl;
        // print_uint(opponent);
        if (i < 4)
        {
            // i think need direction masks
            candidates = opponent & ((player&(~dir_masks[i])) >> shifts[i]);
            // std::cout << "C candidates:" << std::endl;
            // print_uint(candidates);
            while (candidates != 0) {
                // std::cout << "C (candidates>>shifts[i]):" << std::endl;
                candidates = ((candidates&(~dir_masks[i])) >> shifts[i]);
                // print_uint(candidates);
                moves |= empty & candidates;
                // std::cout << "C moves:" << std::endl;
                // print_uint(moves);
                // candidates = ((candidates&(~dir_masks[i])) >> shifts[i]);
                candidates = opponent & candidates;
                // std::cout << "C candidates:" << std::endl;
                // print_uint(candidates);
            }
        } else {
            candidates = opponent & ((player&(~dir_masks[i])) << shifts[i]);
            // std::cout << "C candidates:" << std::endl;
            // print_uint(candidates);
            while (candidates != 0)
            {
                // std::cout << "C (candidates<<shifts[i]):" << std::endl;
                candidates = ((candidates&(~dir_masks[i])) << shifts[i]);
                // print_uint(candidates);
                moves |= empty & candidates;
                // std::cout << "C moves:" << std::endl;
                // print_uint(moves);
                //  candidates = ((candidates&(~dir_masks[i])) >> shifts[i]);
                candidates = opponent & candidates;
                // std::cout << "C candidates:" << std::endl;
                // print_uint(candidates);
                
                
            }
        }
    }
    return moves;
}

int bitCount(u64 bits) {
    u64 print_mask = 0x8000000000000000;
    // std::cout << std::bitset<64>(bits).to_string() << std::endl;
    // std::cout << std::bitset<64>(print_mask).to_string() << std::endl;
    int count = 0;
    for (int i = 0; i < 64; ++i) {
        if ((print_mask & bits)!=0) {
            count++;
        }
        bits<<=1;
    }
    return count;
}

u64 pick_randomly(u64 moves) {
    int num_moves = bitCount(moves);
    srand(time(NULL));
    int choice = rand() % num_moves + 1;
    int scan = 0;
    u64 mask = 0x8000000000000000;
    int position;
    for (int i = 0; i < 64; ++i)
    {
        if ((mask & moves) != 0)
        {
            scan++;
            if (scan == choice) {
                position = i;
                break;
            }
        }
        moves <<= 1;
    }
    return mask >> position;
}

bool is_legal(u64 move, u64 legal_moves) {
    return (move & legal_moves) != 0UL;
}