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

u64 playMinimax(std::tuple<u64, u64> board) {
    return std::get<MOVE>(_minimax(board, 0, 1, 6));
}

std::tuple<u64, int> _minimax(std::tuple<u64, u64> board, int ply, int player, int maxDepth) {
    if (ply >= maxDepth) {
        return std::make_tuple<u64, int>(~0UL, evaluate(board));
    }
    if (player > 0) {
        int maxEval = std::numeric_limits<int>::min();
        std::vector<u64> moveList = get_moves_list(std::get<AI>(board), std::get<OPPONENT>(board));
        if (moveList.size() == 0) {
            moveList.push_back(0UL);
        }
        std::tuple<u64, int> bestMove = std::make_tuple(moveList[0], 0);
        for (int i = 0; i < moveList.size(); ++i) {
            std::tuple<u64, u64> newBoard;
            if (moveList[i] == 0UL) {
                newBoard = std::make_tuple(std::get<AI>(board), std::get<OPPONENT>(board));
            }else {
                newBoard = play(moveList[i], std::get<AI>(board), std::get<OPPONENT>(board), true);
            }
            std::tuple<u64, int> tempMove = _minimax(newBoard, ply+1, -player, maxDepth);
            if (std::get<VALUE>(tempMove) > maxEval) {
                maxEval = std::get<VALUE>(tempMove);
                std::get<VALUE>(bestMove) = std::get<VALUE>(tempMove);
                std::get<MOVE>(bestMove) = moveList[i];
            }
        }
        return bestMove;
    }else {
        int minEval = std::numeric_limits<int>::max();
        std::vector<u64> moveList = get_moves_list(std::get<OPPONENT>(board), std::get<AI>(board));
        if (moveList.size() == 0) {
            moveList.push_back(0UL);
        }
        std::tuple<u64, int> bestMove = std::make_tuple(moveList[0], 0);
        for (int i = 0; i < moveList.size(); ++i) {
            std::tuple<u64, u64> newBoard;
            if (moveList[i] == 0UL) {
                newBoard = std::make_tuple(std::get<AI>(board), std::get<OPPONENT>(board));
            }else {
                newBoard = play(moveList[i], std::get<OPPONENT>(board), std::get<AI>(board), false);
            }
            std::tuple<u64, int> tempMove = _minimax(newBoard, ply+1, -player, maxDepth);
            if (std::get<VALUE>(tempMove) < minEval) {
                minEval = std::get<VALUE>(tempMove);
                std::get<VALUE>(bestMove) = std::get<VALUE>(tempMove);
                std::get<MOVE>(bestMove) = moveList[i];
            }
        }
        return bestMove;
    }   
}

u64 playAlphaBeta(std::tuple<u64, u64> board) {
    int timeForMove = (int)(timeAllocation[moveNumber-1]*(double)timeRemaining);
    // moveTime = timeForMove;
    time_t abStart = time(NULL);
    std::cout << "C ..............Time for move: " << timeForMove << std::endl;
    int i = 2;
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();
    u64 daBest = std::get<MOVE>(_alphaBeta(board, 0, 1, alpha, beta, i));
    while ((time(NULL) - abStart) < timeForMove) {
        i += 2;
        daBest =  std::get<MOVE>(_alphaBeta(board, 0, 1, alpha, beta, i));
    }
    return daBest;
}

std::tuple<u64, int> _alphaBeta(std::tuple<u64, u64> board, int ply, int player, int alpha, int beta, int maxDepth) {
    if (ply >= maxDepth) {
        return std::make_tuple<u64, int>(~0UL, evaluate(board));
    }
    if (player > 0) {
        int maxEval = std::numeric_limits<int>::min();
        std::vector<u64> moveList = get_moves_list(std::get<AI>(board), std::get<OPPONENT>(board));
        if (moveList.size() == 0) {
            moveList.push_back(0UL);
        }
        std::tuple<u64, int> bestMove = std::make_tuple(moveList[0], 0);
        for (int i = 0; i < moveList.size(); ++i) {
            std::tuple<u64, u64> newBoard;
            if (moveList[i] == 0UL) {
                newBoard = std::make_tuple(std::get<AI>(board), std::get<OPPONENT>(board));
            }else {
                newBoard = play(moveList[i], std::get<AI>(board), std::get<OPPONENT>(board), true);
            }
            std::tuple<u64, int> tempMove = _alphaBeta(newBoard, ply+1, -player, alpha, beta, maxDepth);
            if (std::get<VALUE>(tempMove) > maxEval) {
                maxEval = std::get<VALUE>(tempMove);
                std::get<VALUE>(bestMove) = std::get<VALUE>(tempMove);
                std::get<MOVE>(bestMove) = moveList[i];
                alpha = std::max(alpha, maxEval);
            }
            if (maxEval >= beta) {
                break;
            }
        }
        return bestMove;
    }else {
        int minEval = std::numeric_limits<int>::max();
        std::vector<u64> moveList = get_moves_list(std::get<OPPONENT>(board), std::get<AI>(board));
        if (moveList.size() == 0) {
            moveList.push_back(0UL);
        }
        std::tuple<u64, int> bestMove = std::make_tuple(moveList[0], 0);
        for (int i = 0; i < moveList.size(); ++i) {
            std::tuple<u64, u64> newBoard;
            if (moveList[i] == 0UL) {
                newBoard = std::make_tuple(std::get<AI>(board), std::get<OPPONENT>(board));
            }else {
                newBoard = play(moveList[i], std::get<OPPONENT>(board), std::get<AI>(board), false);
            }
            std::tuple<u64, int> tempMove = _alphaBeta(newBoard, ply+1, -player, alpha, beta, maxDepth);
            if (std::get<VALUE>(tempMove) < minEval) {
                minEval = std::get<VALUE>(tempMove);
                std::get<VALUE>(bestMove) = std::get<VALUE>(tempMove);
                std::get<MOVE>(bestMove) = moveList[i];
                beta = std::min(beta, minEval);
            }
            if (minEval <= alpha) {
                break;
            }
        }
        return bestMove;
    }   
}


int evaluate(std::tuple<u64, u64> board) {
    int countSelf = bitCount(std::get<AI>(board));
    int countOpponent = bitCount(std::get<OPPONENT>(board));
    int netPieces = countSelf - countOpponent; 
    if (is_end(std::get<AI>(board), std::get<OPPONENT>(board))) {
        return netPieces * 100000;
    }
    return netPieces;
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
        // print_uint(moves);
        // std::cout << bitCount(moves) << std::endl;
        // std::cout << moveList.size() << std::endl;
        if (bitCount(moves) != moveList.size()) {
            std::cout << "mismatch between moves and moveList sizes" << std::endl;
        }
    }
    return moveList;

}