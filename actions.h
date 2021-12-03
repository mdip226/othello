#if !defined(ACTIONS_H)
#define ACTIONS_H

#include "utils.h"

#define AI 0 
#define OPPONENT 1

// applies a move to a board
u64 _make_move(u64 move, u64 board);

// returns a tuple in the form tuple<player, opponent>
std::tuple<u64, u64> play(u64 move, u64 player, u64 opponent, bool isSelf);

bool is_end(u64 player, u64 opponent);

void send_move(u64 move, bool isBlack);

std::tuple<u64, u64> I_B();

std::tuple<u64, u64> I_W();

void passW();

void passB();

std::tuple<u64, u64> playB(std::string input, std::tuple<u64, u64> board);

std::tuple<u64, u64> playW(std::string input, std::tuple<u64, u64> board);

void end_of_game(std::tuple<u64, u64> board, bool isBlack);

//this means the AI is making it's play (not to be confused with actually playing against itself)
std::tuple<u64, u64> playSelf(std::tuple<u64, u64> board, bool isBlack);

#endif // ACTIONS_H

