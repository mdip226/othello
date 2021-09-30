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

#define AI 0 
#define OPPONENT 1

int main(int argc, char const *argv[])
{
    // u64 test = 0x7F7F7F7F7F7F7F00;
    // print_uint(test);
    u64 white = init_white();
    u64 black = init_black();
    tuple<u64, u64> board;
    // print_uint(~(NORTH | EAST));
    print_board(black, white);
    // print_board(0x20001e1c18040000, 0x1f3f010301000000);
    // print_legal_moves(0x20001e1c18040000, 0x1f3f010301000000, false);
    // print_uint(NORTH);
    // print_uint(NORTH);
    // print_uint(SOUTH);
    // print_uint(EAST);
    // print_uint(WEST);
    // print_uint(NORTH|EAST);
    // print_uint(NORTH|WEST);
    // print_uint(SOUTH|EAST);
    // print_uint(SOUTH|WEST);
    bool isBlack;
    for (string input; getline(cin, input);) {
        if (!input.compare("I B")) {
            //initialize AI as black
            isBlack = true;
            board = make_tuple(black, white);
            // board.white;
            cout << "C initialize AI as black" << endl;
        }
        if (!input.compare("I W")) {
            //initialize AI as white
            isBlack = false;
            board = make_tuple(white, black);
            cout << "C initialize AI as white" << endl;
        }
        if (!input.compare(0, 1, "B")) {
            if (input.length()==1) {
                cout << "C Black passes." << endl;
            }
            else {
                char col = input[2];
                //converts a single char "int" to an int with ascii subtraction
                int row = input[4] - '0';
                cout << "C Black to " << col << " " << row << endl;
                u64 move = col_row_to_bit(col, row);
                get<1>(board) = _make_move(move, black);
            }
        }
        if (!input.compare(0, 1, "W")) {
            if (input.length()==1) {
                cout << "C White passes." << endl;
            }
            else {
                char col = input[2];
                //converts a single char "int" to an int with ascii subtraction
                int row = input[4] - '0';
                cout << "C white to " << col << " " << row << endl;
                u64 move = col_row_to_bit(col, row);
                u64 possible_moves = get_legal_moves(get<OPPONENT>(board), get<AI>(board));
                if ((move & possible_moves) == 0UL) {
                    continue;
                }
                board = play(move, get<OPPONENT>(board), get<AI>(board), false);
                print_board(get<AI>(board), get<OPPONENT>(board));
            }
        }
        if (!input.compare(0, 1, "C")) {
            cout << "C comment...." << endl;
            continue;
        }
        stringstream sstream(input);
        int n;
        if (!(sstream >> n).fail()) {
            cout << "C " << n << endl;
        }
        if (isBlack) {
            cout << "C possible black (AI) moves:" << endl;
            print_legal_moves(get<AI>(board), get<OPPONENT>(board), isBlack);
            u64 possible_moves = get_legal_moves(get<AI>(board), get<OPPONENT>(board));
            u64 move = pick_randomly(possible_moves);
            if ((possible_moves & move) == 0UL) {
                cout << "C ERROR IN either get_legal_moves() or pick_randomly()";
            }
            cout << "C possible_chosen:" << endl;
            print_uint(move);
            board = play(move, get<AI>(board), get<OPPONENT>(board), isBlack);
            print_board(get<AI>(board), get<OPPONENT>(board));
            cout << "C Your possible_moves:" << endl;
            print_legal_moves(get<AI>(board), get<OPPONENT>(board), false);
        }else {
            print_board(get<AI>(board), get<OPPONENT>(board));
        }
    }
    return 0;
}
