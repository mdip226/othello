#include <cstdint>
#include <iostream>
#include <bitset>
#include "debug.h"

uint64_t get_legal_moves(uint64_t player, uint64_t opponent) {
    uint64_t full = player | opponent;
    uint64_t mask = 0b0000000000000000000000000000000000000000000000000000000000000000;
    uint64_t empty = (~full) & (~mask);
    uint64_t moves = 0b0000000000000000000000000000000000000000000000000000000000000000;
    uint64_t candidates;
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

int bitCount(uint64_t bits) {
    uint64_t print_mask = 0x8000000000000000;
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

uint64_t pick_randomly(uint64_t moves) {
    int num_moves = bitCount(moves);
    srand(time(NULL));
    int choice = rand() % num_moves + 1;
    int scan = 0;
    uint64_t mask = 0x8000000000000000;
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