#include <cstdint>
#include <iostream>
#include <bitset>

void print_board(uint64_t black, uint64_t white)
{
    uint64_t mask = 0b1000000000000000000000000000000000000000000000000000000000000000;
    std::cout << "  a b c d e f g h" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << i+1 << " ";
        for (int j = 0; j < 8; ++j)
        {
            if ((white & mask) != 0)
            {
                std::cout << "W ";
            }
            else if ((black & mask) != 0)
            {
                std::cout << "B ";
            }
            else
            {
                std::cout << "- ";
            }
            black = black << 1;
            white = white << 1;
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
void print_uint(uint64_t bits) {
    uint64_t mask = 0b1000000000000000000000000000000000000000000000000000000000000000;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if ((bits & mask) != 0)
            {
                std::cout << "X ";
            }
            else
            {
                std::cout << "- ";
            }
            bits <<= 1;
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void print_legal_moves(uint64_t player, uint64_t opponent)
{
    uint64_t full = player | opponent;
    uint64_t mask = 0b0000000000000000000000000000000000000000000000000000000000000000;
    uint64_t empty = (~full) & (~mask);
    uint64_t moves = 0b0000000000000000000000000000000000000000000000000000000000000000;
    uint64_t candidates;
    int cols = 8;
    for (int i = 0; i < 8; ++i)
    {
        int shift = 1;
        if (i != 2 && i != 6)
        {
            shift = cols;
        }
        if (i == 1 || i ==  5)
        {
            shift++;
        }
        if (i == 3 || i == 7 )
        {
            shift--;
        }
        if (i < 4)
        {
            candidates = opponent & (player >> shift);
            while (candidates != 0UL)
            {
                moves |= empty & (candidates >> shift);
                candidates = opponent & (candidates >> shift);
            }
        }
        else
        {
            candidates = opponent & (player << shift);
            while (candidates != 0UL)
            {
                moves |= empty & (candidates << shift);
                candidates = opponent & (candidates << shift);
            }
        }
        // std::cout << std::bitset<64>(moves).to_string() << std::endl;
        // print_uint(moves);
    }
    uint64_t print_mask = 0b1000000000000000000000000000000000000000000000000000000000000000;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if ((player & print_mask) != 0)
            {
                std::cout << "W ";
            }
            else if ((opponent & print_mask) != 0)
            {
                std::cout << "B ";
            }
            else if ((moves & print_mask) != 0)
            {
                std::cout << "X ";
            }
            else
            {
                std::cout << "- ";
            }
            opponent = opponent << 1;
            player = player << 1;
            moves = moves << 1;
        }
        std::cout << "\n";
    }
}
