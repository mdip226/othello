#if !defined(MINMAX_H)
#define MINMAX_H

u64 playAlphaBeta(std::tuple<u64, u64> board);

u64 _alphaBeta(std::tuple<u64, u64> board, int ply, int player, int alpha, int beta, int maxDepth);

std::vector<u64> get_moves_list(u64 player, u64 opponent);


#endif // MINMAX_H

