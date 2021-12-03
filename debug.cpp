#include <iostream>
#include "moves.h"
#include "utils.h"

void print_board(u64 black, u64 white) {
    u64 mask = 0x8000000000000000;
    
    std::cout << "C   a b c d e f g h" << std::endl;
    for (int i = 0; i < 8; ++i) {
        std::cout << "C " << i+1 << " ";
        for (int j = 0; j < 8; ++j) {
            if ((white & mask) != 0UL) {
                std::cout << "W ";
            } else if ((black & mask) != 0UL) {
                std::cout << "B ";
            }else {
                std::cout << "- ";
            }
            black <<= 1;
            white <<= 1;
        }
        std::cout << "\n";
    }
    std::cout << "C \n";
}

void print_uint(u64 bits) {
    u64 mask = 0x8000000000000000;
    std::cout << "C   a b c d e f g h" << std::endl;
    for (int i = 0; i < 8; ++i) {
        std::cout << "C " << i + 1 << " ";
        for (int j = 0; j < 8; ++j) {
            if ((bits & mask) != 0UL) {
                std::cout << "X ";
            }else {
                std::cout << "- ";
            }
            bits <<= 1;
        }
        std::cout << "\n";
    }
    std::cout << "C \n";
}

void print_legal_moves(u64 black, u64 white, bool isBlack) {
    u64 moves;
    if (isBlack) {
        moves = get_legal_moves(black, white);
    }else {
        moves = get_legal_moves(white, black);
    }
    u64 mask = 0x8000000000000000;
    std::cout << "C   a b c d e f g h" << std::endl;
    for (int i = 0; i < 8; ++i) {
        std::cout << "C " << i + 1 << " ";
        for (int j = 0; j < 8; ++j) {
            if ((white & mask) != 0) {
                std::cout << "W ";
            }
            else if ((black & mask) != 0) {
                std::cout << "B ";
            }
            else if ((moves & mask) != 0) {
                std::cout << "@ ";
            }else {
                std::cout << "- ";
            }
            black <<= 1;
            white <<= 1;
            moves <<= 1;
        }
        std::cout << "\n";
    }
    std::cout << "C \n";
}
