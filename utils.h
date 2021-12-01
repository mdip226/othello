#if !defined(UTILS_H)
#define UTILS_H

#include <cstdint>

typedef uint64_t u64;

#define NORTH2 0xFFFF000000000000UL
#define EAST2 0x0303030303030303UL
#define SOUTH2 0x000000000000FFFFUL
#define WEST2 0xC0C0C0C0C0C0C0C0UL
#define NORTH 0xFF00000000000000UL
#define EAST 0x0101010101010101UL
#define SOUTH 0x00000000000000FFUL
#define WEST 0x8080808080808080UL
// #define SOUTHWEST 0x00FEFEFEFEFEFEFEUL
// #define SOUTH 0x00FFFFFFFFFFFFFFUL
// #define SOUTHEAST 0x007F7F7F7F7F7F7FUL
// #define EAST 0x7F7F7F7F7F7F7F7FUL
// #define NORTHEAST 0x7F7F7F7F7F7F7F00UL
#define MOVE 0
#define VALUE 1

extern double timeAllocation[];
//  = {0.015, 0.015, 0.015, 0.015, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025,
//                                     0.048,  0.048, 0.048, 0.048, 0.048, 0.048, 0.050, 0.051, 0.052, 0.053,
//                                     0.044,  0.045, 0.049, 0.049, 0.049, 0.051, 0.053, 0.055, 0.057, 0.059,
//                                     0.060, 0.060, 0.061, 0.062, 0.063, 0.064, 0.065, 0.065, 0.065, 0.065,
//                                     0.167, 0.168, 0.169, 0.169, 0.171, 0.172, 0.173, 0.175, 0.180, 0.180,
//                                     0.181, 0.187, 0.196, 0.199, 0.220, 0.220, 0.220, 0.220, 0.220, 0.220,
//                                     0.220, 0.250, 0.250, 0.250, 0.250, 0.250, 0.250, 0.250, 0.250, 0.250
//                                   };

extern int moveNumber;//  = 0;
extern bool timeUp;//  = false;
extern int timeRemaining;//  = 600;
extern int moveTime;

u64 col_row_to_bit(char col, int row);
u64 init_black();
u64 init_white();


#endif // UTILS_H
