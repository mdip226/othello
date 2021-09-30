#include <cstdint>
#include <iostream>
#include <bitset>
#include "debug.h"
#include "utils.h"

int shifts[] = {1,-1};

u64 get_legal_moves(u64 player, u64 opponent) {
    u64 full = player | opponent;
    u64 mask = 0b0000000000000000000000000000000000000000000000000000000000000000;
    u64 empty = (~full) & (~mask);
    u64 moves = 0b0000000000000000000000000000000000000000000000000000000000000000;
    u64 candidates;
    int cols = 8;
    for (int i = 0; i < 8; ++i)
    {
        // std::cout << "C " << i << std::endl;
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
            // i think need direction masks
            candidates = opponent & (player >> shift);
            switch (i)
            {
            case 0:
                candidates &= (~SOUTH);
                break;
            case 1:
                candidates &= (~(SOUTH|EAST));
                break;
            case 2:
                candidates &= (~EAST);
                break;
            case 3:
                candidates &= (~(SOUTH|WEST));
                break;
            case 4:
                candidates &= (~NORTH);
                break;
            case 5:
                candidates &= (~(NORTH|WEST));
                break;
            case 6:
                candidates &= (~WEST);
                break;
            case 7:
                candidates &= (~(NORTH|EAST));
                break;
            default:
                break;
            }
            // std::cout << "C candidates:" << std::endl;
            // print_uint(candidates);
            while (candidates != 0)
            {
                // std::cout << "C (candidates>>shift):" << std::endl;
                // print_uint(candidates>>shift);
                moves |= empty & (candidates >> shift);
                // std::cout << "C moves:" << std::endl;
                // print_uint(moves);
                candidates = opponent & (candidates >> shift);
                // std::cout << "C candidates:" << std::endl;
                // print_uint(candidates);
                switch (i)
                {
                case 0:
                    candidates &= (~SOUTH);
                    break;
                case 1:
                    candidates &= (~(SOUTH | EAST));
                    break;
                case 2:
                    candidates &= (~EAST);
                    break;
                case 3:
                    candidates &= (~(SOUTH | WEST));
                    break;
                case 4:
                    candidates &= (~NORTH);
                    break;
                case 5:
                    candidates &= (~(NORTH | WEST));
                    break;
                case 6:
                    candidates &= (~WEST);
                    break;
                case 7:
                    candidates &= (~(NORTH | EAST));
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            switch (i)
            {
            case 0:
                candidates &= (~SOUTH);
                break;
            case 1:
                candidates &= (~(SOUTH | EAST));
                break;
            case 2:
                candidates &= (~EAST);
                break;
            case 3:
                candidates &= (~(SOUTH | WEST));
                break;
            case 4:
                candidates &= (~NORTH);
                break;
            case 5:
                candidates &= (~(NORTH | WEST));
                break;
            case 6:
                candidates &= (~WEST);
                break;
            case 7:
                candidates &= (~(NORTH | EAST));
                break;
            default:
                break;
            }
            candidates = opponent & (player << shift);
            // std::cout << "C candidates:" << std::endl;
            // print_uint(candidates);
            while (candidates != 0)
            {
                // std::cout << "C (candidates<<shift):" << std::endl;
                // print_uint(candidates<<shift);
                moves |= empty & (candidates << shift);
                // std::cout << "C moves:" << std::endl;
                // print_uint(moves);
                candidates = opponent & (candidates << shift);
                // std::cout << "C candidates:" << std::endl;
                // print_uint(candidates);
                switch (i)
                {
                case 0:
                    candidates &= (~SOUTH);
                    break;
                case 1:
                    candidates &= (~(SOUTH | EAST));
                    break;
                case 2:
                    candidates &= (~EAST);
                    break;
                case 3:
                    candidates &= (~(SOUTH | WEST));
                    break;
                case 4:
                    candidates &= (~NORTH);
                    break;
                case 5:
                    candidates &= (~(NORTH | WEST));
                    break;
                case 6:
                    candidates &= (~WEST);
                    break;
                case 7:
                    candidates &= (~(NORTH | EAST));
                    break;
                default:
                    break;
                }
            }
        }
        // std::cout << std::bitset<64>(moves).to_string() << std::endl;
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