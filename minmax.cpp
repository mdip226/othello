#include <iostream>
#include <string>
#include <tuple>
#include <limits>
#include <vector>

#include "debug.h"
#include "moves.h"
#include "actions.h"
#include "utils.h"
#include "minmax.h"

u64 playAlphaBeta(std::tuple<u64, u64> board) {
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();
    std::cout << "alpha: " << alpha << std::endl;
    std::cout << "beta: " << beta << std::endl;
    return _alphaBeta(board, 0, 1, alpha, beta, 2);
}

u64 _alphaBeta(std::tuple<u64, u64> board, int ply, int player, int alpha, int beta, int maxDepth) {
    if (ply >= maxDepth) {
        return 0UL;
    }else {
        std::vector<u64> moveList = get_moves_list(std::get<AI>(board), std::get<OPPONENT>(board));
        if (moveList.size() == 0) {
            moveList.push_back(0UL);
        }
        u64 bestMove = moveList[0];
        for (int i = 0; i < moveList.size(); ++i) {
            std::tuple<u64, u64> newBoard;
            if (player > 1) {
                newBoard = play(moveList[i], std::get<AI>(board), std::get<OPPONENT>(board), true);
            }else {
                newBoard = play(moveList[i], std::get<OPPONENT>(board), std::get<AI>(board), false);
            }
            u64 tempMove = _alphaBeta(newBoard, ply+1, -player, -beta, -alpha, maxDepth);
        }
    }
    return 0;
}

int evaluate(std::tuple<u64, u64> board) {
    int countSelf = bitCount(std::get<AI>(board));
    int countOpponent = bitCount(std::get<OPPONENT>(board));
    return countSelf - countOpponent;
}

std::vector<u64> get_moves_list(u64 player, u64 opponent) {
    u64 moves = get_legal_moves(player, opponent);
    std::vector<u64> moveList;
    u64 scanner = 1UL;
    for (int i = 0; i < 64; ++i) {
        if ((scanner & moves) != 0UL) {
            // TODO start ordering moves here
            moveList.push_back(scanner);
        }
        scanner <<= 1;
    }
    if (DEBUG) {
        print_uint(moves);
        // std::cout << bitCount(moves) << std::endl;
        // std::cout << moveList.size() << std::endl;
        if (bitCount(moves) != moveList.size()) {
            std::cout << "mismatch between moves and moveList sizes" << std::endl;
        }
    }
    return moveList;

}