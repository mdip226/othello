#include <iostream>
#include <sstream>
#include <string>
#include <cstdint>
#include <bitset>
#include <tuple>
#include <time.h>
#include "debug.h"
#include "moves.h"
#include "actions.h"
#include "utils.h"
using namespace std;


int main(int argc, char const *argv[])
{
    bool isBlack;
    bool isInteractive = false;
    // bool isFirstTurn = true;
    // bool playItself = false;
    for (int i = 1; i < argc; ++i) {
        // if (string(argv[i]) == "-s") {
        //     playItself = true;
        // }
        if (string(argv[i]) == "-i") {
            isInteractive = true;
        }
    }
    u64 white = init_white();
    u64 black = init_black();
    tuple<u64, u64> board;
    print_board(black, white);

    for (string input; getline(cin, input);) {
        cout << "C ..............Time Remaining: " << timeRemaining << endl;
        time_t start = time(NULL);
        // ignore comments
        if (!input.compare(0, 1, "C")) {
            continue;
        }
        // initialize self as black, then play
        if (!input.compare("I B")) {
            board = I_B();
            isBlack = true;
        }
        // initialize self as white, then wait for black to play
        if (!input.compare("I W")) {
            board = I_W();
            isBlack = false;
            continue;
        }
        if (DEBUG) {
            if (isBlack) {
                print_board(std::get<AI>(board), std::get<OPPONENT>(board));
            }else {
                print_board(std::get<OPPONENT>(board), std::get<AI>(board));
            }
        }
        // Opponent as black, update board state with their move, or do nothing if they pass
        if (!input.compare(0, 1, "B")) {
            if (input.length() == 1) {
                passB();
            }else {
                board = playB(input, board);
            }
        }
        // Opponent as white, update board state with their move, or do nothing if they pass
        if (!input.compare(0, 1, "W")) {
            if (input.length()==1) {
                passW();
            }else {
                board = playW(input, board);
            }
        }

        // check for endgame
        bool isEnd = is_end(get<AI>(board), get<OPPONENT>(board));
        // otherwise, make my move
        if (!isEnd) {
            board = playSelf(board, isBlack);
            
        }
        time_t end = time(NULL);
        int moveTime = end-start;
        timeRemaining -= moveTime;
        cout << "C ..............Time Remaining: " << timeRemaining << endl;

        // TODO cleanup
        // if (!input.compare("") && isInteractive) {
        //     u64 legal_moves = get_legal_moves(get<OPPONENT>(board), get<AI>(board));
        //     if (legal_moves != 0UL) {
        //         u64 move = pick_randomly(legal_moves);
        //         bool isLegal = is_legal(move, legal_moves);
        //         if (isLegal)
        //         {
        //             if (isBlack) {
        //                 board = play(move, get<OPPONENT>(board), get<AI>(board), false);
        //                 print_board(get<AI>(board), get<OPPONENT>(board));
        //             }else {
        //                 board = play(move, get<OPPONENT>(board), get<AI>(board), false);
        //                 print_board(get<OPPONENT>(board), get<AI>(board));
        //             }
        //         }else {
        //             cout << "C ERROR in either get_legal_moves() or pick_randomly()";
        //         }
        //     }
        //     // isFirstTurn = false;
        // }
        // if (isInteractive) {
        //     cout << "C Just Press enter to pick randomly." << endl;
        // }
    }
    return 0;
}
