#include <tuple>
#include <string>
#include <iostream>
#include "utils.h"
#include "debug.h"
#include "moves.h"
#include <stdlib.h>
#include "actions.h"
#include "minmax.h"



u64 _make_move(u64 move, u64 board)
{
    return move | board;
}

void send_move(u64 move, bool isBlack) {

    char color = isBlack ? 'B' : 'W';

    if (move == 0UL) {
        if (DEBUG) {
            std::string _color = isBlack ? "Black" : "White";
            std::cout << "C .............." << _color << " (Self) Passes." << std::endl;
        }
        std::cout << color << std::endl;
        return;
    }

    char cols[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    int rows[] = {1, 2, 3, 4, 5, 6, 7, 8};
    char col;
    int row;
    u64 mask = 0x8000000000000000;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((mask & move) != 0UL) {
                std::cout << color << " " << cols[j] << " " << rows[i] << std::endl;
                return;
            }
            move <<= 1;
        }
    }
}


std::tuple<u64, u64> play(u64 move, u64 player, u64 opponent, bool isSelf) {
    // dont forget to check whether it is a legal move or not....

    int shifts[] = {1,7,8,9,1,7,8,9};
    u64 dir_masks[] = {EAST,SOUTH|WEST,SOUTH,SOUTH|EAST,WEST,NORTH|EAST,NORTH,NORTH|WEST};
    player = _make_move(move, player);
    u64 flips_final = 0x0000000000000000;
    u64 candidate;
    for (int i = 0; i < 8; ++i) {
        if (i < 4) {
            u64 flips = 0x0000000000000000;
            u64 scanner = (move & ~dir_masks[i]) >> shifts[i];
            // std::cout << i << std::endl;
            // print_uint(scanner);
            candidate = opponent & scanner;
            // print_uint(candidate);
            while (candidate != 0UL)
            {
                flips |= candidate;
                scanner = (scanner & ~dir_masks[i]) >> shifts[i];
                if ((player & scanner) != 0UL) {
                    flips_final |= flips;
                    break;
                }
                candidate = opponent & scanner;
            }
        }else {
            u64 flips = 0x0000000000000000;
            u64 scanner = (move & ~dir_masks[i]) << shifts[i];
            // std::cout << i << std::endl;
            // print_uint(scanner);
            candidate = opponent & scanner;
            // print_uint(candidate);
            while (candidate != 0UL) {
                flips |= candidate;
                scanner = (scanner & ~dir_masks[i]) << shifts[i];
                if ((player & scanner) != 0UL) {
                    flips_final |= flips;
                    break;
                }
                candidate = opponent & scanner;
            }
        }   
    }

    opponent = (~flips_final) & opponent;
    player |= flips_final;
    if (isSelf) {
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

std::tuple<u64, u64> I_B() {
    u64 white = init_white();
    u64 black = init_black();
    std::tuple<u64, u64> board = std::make_tuple(black, white);
    std::cout << "C ..............Initializing SELF as black" << std::endl;
    std::cout << "R B" << std::endl;
    return board;
}

std::tuple<u64, u64> I_W() {
    u64 white = init_white();
    u64 black = init_black();
    std::tuple<u64, u64> board = std::make_tuple(white, black);
    std::cout << "C ..............Initializing SELF as white" << std::endl;
    std::cout << "R W" << std::endl;
    return board;
}

void passB() {
    std::cout << "C ..............Black passes." << std::endl;
    return;
}

void passW() {
    std::cout << "C ..............White passes." << std::endl;
    return;
}

std::tuple<u64, u64> playB(std::string input, std::tuple<u64, u64> board) {
    char col = input[2];
    //converts a single char "int" to an int with ascii subtraction
    int row = input[4] - '0';
    std::cout << "C ..............Black(opponent) to " << col << " " << row << std::endl;
    u64 move = col_row_to_bit(col, row);
    if (DEBUG) {
        print_uint(move);
    }
    u64 legal_moves = get_legal_moves(std::get<OPPONENT>(board), std::get<AI>(board));
    if (DEBUG) {
        std::cout << "C ..............legal_moves:" << std::endl;
        print_uint(legal_moves);
    }

    bool isLegalMove = is_legal(move, legal_moves);
    if (isLegalMove) {
        if (DEBUG) {
            std::cout << "C ..............isLegalMove!" << std::endl;
        }
        board = play(move, std::get<OPPONENT>(board), std::get<AI>(board), false);
        if (DEBUG) {
            print_board(std::get<OPPONENT>(board), std::get<AI>(board));
        }
        return board;
    }else {
        std::cout << "C ..............Black(Opponent) Illegal Move:\nC ..............B " << col << " " << row << std::endl;
        exit(1);
    }
}

std::tuple<u64, u64> playW(std::string input, std::tuple<u64, u64> board) {
    char col = input[2];
    //converts a single char "int" to an int with ascii subtraction
    int row = input[4] - '0';
    std::cout << "C ..............White(opponent) to " << col << " " << row << std::endl;
    u64 move = col_row_to_bit(col, row);
    if (DEBUG) {
        print_uint(move);
    }
    u64 legal_moves = get_legal_moves(std::get<OPPONENT>(board), std::get<AI>(board));
    if (DEBUG) {
        std::cout << "C ..............legal_moves:" << std::endl;
        print_uint(legal_moves);
    }
    bool isLegalMove = is_legal(move, legal_moves);
    if (isLegalMove) {
        if (DEBUG) {
            std::cout << "C ..............isLegalMove!" << std::endl;
        }
        board = play(move, std::get<OPPONENT>(board), std::get<AI>(board), false);
        if (DEBUG) {
            print_board(std::get<AI>(board), std::get<OPPONENT>(board));
        }
        return board;
    }else {
        std::cout << "C ..............White(Opponent) Illegal Move:\nC ..............W " << col << " " << row << std::endl;
        exit(1);
    }
}

void end_of_game(std::tuple<u64, u64> board, bool isBlack) {
    int countBlack, countWhite;
    std::string toggle;
    if (isBlack) {
        countBlack = bitCount(std::get<AI>(board));
        countWhite = bitCount(std::get<OPPONENT>(board));
    }else {
        countBlack = bitCount(std::get<OPPONENT>(board));
        countWhite = bitCount(std::get<AI>(board));
    }
    if (DEBUG) {
        std::cout << "C ..............countBlack:" << countBlack << std::endl;
        std::cout << "C ..............countWhite:" << countWhite << std::endl;
    }
    if (countBlack > countWhite) {
        toggle = isBlack ? "Self" : "Opponent";
        std::cout << "C ..............Black("<< toggle << ")  Wins!" << std::endl;
    }else if (countWhite > countBlack) {
        toggle = isBlack ? "Opponent" : "Self";
        std::cout << "C ..............White Wins!" << std::endl;
    }
    std::cout << countBlack << std::endl;
    exit(0);
}

std::tuple<u64, u64> playSelf(std::tuple<u64, u64> board, bool isBlack) {
    moveNumber++;
    std::string color = isBlack ? "Black" : "White";
    if (DEBUG) {
        std::cout << "C ..............Possible " << color << " (Self) moves:" << std::endl;
        if (isBlack) {
            print_legal_moves(std::get<AI>(board), std::get<OPPONENT>(board), isBlack);
        }else {
            print_legal_moves(std::get<OPPONENT>(board), std::get<AI>(board), isBlack);
        }
    }
    u64 legal_moves = get_legal_moves(std::get<AI>(board), std::get<OPPONENT>(board));
    if (legal_moves != 0UL) {
        u64 move = playAlphaBeta(board);
        bool isLegal = is_legal(move, legal_moves);
        if (isLegal) {
            board = play(move, std::get<AI>(board), std::get<OPPONENT>(board), true);
        }
        else {
            std::cout << "C ..............ERROR in either get_legal_moves() or pick_randomly()";
        }
        if (DEBUG) {
            std::cout << "C ..............possible_chosen:" << std::endl;
            print_uint(move);
            if (isBlack) {
                print_board(std::get<AI>(board), std::get<OPPONENT>(board));
                std::cout << "C ..............White (Opponent) possible_moves:" << std::endl;
                print_legal_moves(std::get<AI>(board), std::get<OPPONENT>(board), false);
            }else {
                print_board(std::get<OPPONENT>(board), std::get<AI>(board));
                std::cout << "C ..............Black (Opponent) possible_moves:" << std::endl;
                print_legal_moves(std::get<OPPONENT>(board), std::get<AI>(board), true);
            }
        }
        send_move(move, isBlack);
        return board;
        
    }else{
        send_move(0UL, isBlack);
        return board;
    }
}