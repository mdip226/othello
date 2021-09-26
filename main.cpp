#include <iostream>
#include <sstream>
#include <string>
#include <cstdint>
#include <bitset>
#include "debug.h"
#include "moves.h"
#include "actions.h"
#include "utils.h"
using namespace std;

int main(int argc, char const *argv[])
{
    uint64_t white = init_white();
    uint64_t black = init_white();
    print_board(black, white);
    // uint64_t moves = get_legal_moves(white, black);
    // print_uint(moves);
    // int num_moves = bitCount(moves);
    // cout << "number of moves: " << num_moves << endl;
    // print_legal_moves(white, black);
    bool isBlack;
    for (string input; getline(cin, input);) {
        if (!input.compare("I B")) {
            //initialize AI as black
            isBlack = true;
            cout << "C initialize as black" << endl;
        }
        if (!input.compare("I W")) {
            //initialize AI as white
            isBlack = false;
            cout << "C initialize as white" << endl;
        }
        if (isBlack) {
            uint64_t possible_moves = get_legal_moves(black, white);
            uint64_t move = pick_randomly(possible_moves);
            print_uint(possible_moves);
            print_uint(move);

        }
        if (!input.compare(0, 1, "B")) {
            cout << "C black....";
            if (input.length()==1) {
                cout << "passes." << endl;
            }
            else {
                char col = input[2];
                //converts a single char "int" to an int with ascii subtraction
                int row = input[4] - '0';
                cout << "moves to " << col << " " << row << endl;
                uint64_t move = row_col_to_bit(col, row);
                black = make_move(move, black);
            }
        }
        if (!input.compare(0, 1, "W")) {
            cout << "C white....";
            if (input.length()==1) {
                cout << "passes." << endl;
            }
            else {
                char col = input[2];
                //converts a single char "int" to an int with ascii subtraction
                int row = input[4] - '0';
                uint64_t move = row_col_to_bit(col, row);
                white = make_move(move, white);
                print_board(black, white);
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
    }
    return 0;
}
