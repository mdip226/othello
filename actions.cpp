#include <cstdint>

uint64_t make_move(uint64_t move, uint64_t board)
{
    return move | board;
}

