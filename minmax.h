#if !defined(MINMAX_H)
#define MINMAX_H

#include <vector>

u64 playMinimax(std::tuple<u64, u64> board);

std::tuple<u64, int> _minimax(std::tuple<u64, u64> board, int ply, int player, int maxDepth);

u64 playAlphaBeta(std::tuple<u64, u64> board);

std::tuple<u64, int> _alphaBeta(std::tuple<u64, u64> board, int ply, int player, int alpha, int beta, int maxDepth);

std::vector<u64> get_moves_list(u64 player, u64 opponent);

int evaluate(std::tuple<u64, u64> board);


#endif // MINMAX_H

