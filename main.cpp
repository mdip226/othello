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
    u64 white = init_white();
    u64 black = init_black();
    tuple<u64, u64> board;
    print_board(black, white);
    bool isBlack;
    bool isInteractive;
    bool isFirstTurn = true;
    bool playItself = true;

    for (string input; getline(cin, input);) {
        if (!input.compare("I B")) {
            //initialize AI as black
            isBlack = true;
            board = make_tuple(black, white);
            cout << "C initializing AI as black" << endl;
        }
        if (!input.compare("I W")) {
            //initialize AI as white
            isBlack = false;
            board = make_tuple(white, black);
            cout << "C initializing AI as white" << endl;
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
                u64 legal_moves = get_legal_moves(get<OPPONENT>(board), get<AI>(board));
                bool isLegalMove = is_legal(move, legal_moves);
                if (isLegalMove) {
                    board = play(move, get<OPPONENT>(board), get<AI>(board), false);
                    print_board(get<OPPONENT>(board), get<AI>(board));
                }else {
                    cout << "C Illegal Move:\nC B " << col << " " << row << endl;
                    exit(1); 
                }
                isFirstTurn = false;
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
                u64 legal_moves = get_legal_moves(get<OPPONENT>(board), get<AI>(board));
                bool isLegalMove = is_legal(move, legal_moves);
                if (isLegalMove)
                {
                    board = play(move, get<OPPONENT>(board), get<AI>(board), false);
                    print_board(get<AI>(board), get<OPPONENT>(board));
                }
                else
                {
                    cout << "C Illegal Move:\nC W " << col << " " << row << endl;
                    exit(1);
                }
                // print_board(get<AI>(board), get<OPPONENT>(board));
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
        bool isEnd = is_end(get<AI>(board), get<OPPONENT>(board));
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
        }
        else if (isBlack) {
            // cout << "C possible black (AI) moves:" << endl;
            // print_legal_moves(get<AI>(board), get<OPPONENT>(board), isBlack);
            u64 legal_moves = get_legal_moves(get<AI>(board), get<OPPONENT>(board));
            u64 move = pick_randomly(legal_moves);
            bool isLegal = is_legal(move, legal_moves);
            if (isLegal)
            {
                board = play(move, get<AI>(board), get<OPPONENT>(board), true);
            }
            else {
                cout << "C ERROR in either get_legal_moves() or pick_randomly()";
            }
            // cout << "C possible_chosen:" << endl;
            // print_uint(move);
            print_board(get<AI>(board), get<OPPONENT>(board));
            cout << "C Your possible_moves:" << endl;
            print_legal_moves(get<AI>(board), get<OPPONENT>(board), false);
        }else if (!isBlack && !isFirstTurn){
            // cout << "C !isBlack && !isFirstTurn" << endl;
            // print_board(get<OPPONENT>(board), get<AI>(board));
            u64 legal_moves = get_legal_moves(get<AI>(board), get<OPPONENT>(board));
            u64 move = pick_randomly(legal_moves);
            bool isLegal = is_legal(move, legal_moves);
            if (isLegal) {
                board = play(move, get<AI>(board), get<OPPONENT>(board), true);
            }else {
                cout << "C ERROR in either get_legal_moves() or pick_randomly()";
            }
            print_board(get<OPPONENT>(board), get<AI>(board));
            cout << "C Your possible_moves:" << endl;
            print_legal_moves(get<OPPONENT>(board), get<AI>(board), true);
        }
    }
    return 0;
}
