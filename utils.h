#if !defined(UTILS_H)
#define UTILS_H

#include <cstdint>

typedef uint64_t u64;

#define NORTH 0xFFFFFFFFFFFFFF00UL
#define NORTHWEST 0xFEFEFEFEFEFEFE00UL
#define WEST 0xFEFEFEFEFEFEFEFEUL
#define SOUTHWEST 0x00FEFEFEFEFEFEFEUL
#define SOUTH 0x00FFFFFFFFFFFFFFUL
#define SOUTHEAST 0x007F7F7F7F7F7F7FUL
#define EAST 0x7F7F7F7F7F7F7F7FUL
#define NORTHEAST 0x7F7F7F7F7F7F7F00UL

u64 col_row_to_bit(char col, int row);
u64 init_black();
u64 init_white();


#endif // UTILS_H
