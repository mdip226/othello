#include <iostream>
#include <sstream>
#include <string>
#include <cstdint>
#include <bitset>
#include <tuple>
#include "debug.h"
#include "moves.h"
#include "actions.h"
#include "utils.h"
using namespace std;


int main(int argc, char const *argv[])
{
    bool isBlack;
    bool isInteractive = false;
    bool isFirstTurn = true;
    bool playItself = false;
    for (int i = 1; i < argc; ++i) {
        if (string(argv[i]) == "-s") {
            playItself = true;
        }
        if (string(argv[i]) == "-i") {
            isInteractive = true;
        }
    }
    u64 white = init_white();
    u64 black = init_black();
    tuple<u64, u64> board;
    print_board(black, white);

    for (string input; getline(cin, input);) {
        if (!input.compare(0, 1, "C")) {
            continue;
        }
        if (!input.compare("I B")) {
            board = I_B();
            isBlack = true;
        }
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
        if (!input.compare(0, 1, "B")) {
            if (input.length() == 1) {
                passB();
            }
            else {
                board = playB(input, board);
            }
        }
        if (!input.compare(0, 1, "W")) {
            if (input.length()==1) {
                passW();
            }
            else {
                board = playW(input, board);
            }
        }
        
        stringstream sstream(input);
        int n;
        if (!(sstream >> n).fail()) {
            cout << "C " << n << endl;
            exit(0);
        }
        bool isEnd = is_end(get<AI>(board), get<OPPONENT>(board));
        if (isEnd) {
            end_of_game(board, isBlack);
        }
        else {
            board = playSelf(board, isBlack);
        }
        if (!input.compare("") && isInteractive) {
            u64 legal_moves = get_legal_moves(get<OPPONENT>(board), get<AI>(board));
            if (legal_moves != 0UL) {
                u64 move = pick_randomly(legal_moves);
                bool isLegal = is_legal(move, legal_moves);
                if (isLegal)
                {
                    if (isBlack) {
                        board = play(move, get<OPPONENT>(board), get<AI>(board), false);
                        print_board(get<AI>(board), get<OPPONENT>(board));
                    }else {
                        board = play(move, get<OPPONENT>(board), get<AI>(board), false);
                        print_board(get<OPPONENT>(board), get<AI>(board));
                    }
                }
                else {
                    cout << "C ERROR in either get_legal_moves() or pick_randomly()";
                }
            }
            isFirstTurn = false;
        }
        if (isInteractive) {
            cout << "C Just Press enter to pick randomly." << endl;
        }
        isEnd = is_end(get<AI>(board), get<OPPONENT>(board));
        if (isEnd) {
            int countBlack, countWhite;
            if (isBlack) {
                countBlack = bitCount(get<AI>(board));
                countWhite = bitCount(get<OPPONENT>(board));
            }else {
                countBlack = bitCount(get<OPPONENT>(board));
                countWhite = bitCount(get<AI>(board));
            }
            cout << countBlack << endl;
            if (countBlack > countWhite) {
                cout << "C Black Wins!" << endl;
            }else if (countWhite > countBlack) {
                cout << "C White Wins!" << endl;
            }
            exit(0);
        }
    }
    return 0;
}
