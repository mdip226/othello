from textwrap import wrap
from ctypes import c_uint64 as u64


def print_bitboard(board):             # v split for spaces          v split for newlines
    board = format(board.value, "b").zfill(64)
    # len(board)
    # print(board)
    print('\n'.join([' '.join(wrap(line, 1)) for line in wrap(board, 8)]))


def flipVertical(x):
    return ((x << 56)) |\
    ((x << 40) & u64(0x00ff000000000000)) |\
    ((x << 24) & u64(0x0000ff0000000000)) |\
    ((x << 8) & u64(0x000000ff00000000)) |\
    ((x >> 8) & u64(0x00000000ff000000)) |\
    ((x >> 24) & u64(0x0000000000ff0000)) |\
    ((x >> 40) & u64(0x000000000000ff00)) |\
    ((x >> 56))

def rotateCW(x):
    return u64(u64((u64(x.value << 56).value>>49)).value|\
           u64((u64(x.value << 47).value >> 50)).value|\
           u64((u64(x.value << 56).value >> 51)).value|\
           u64((u64(x.value << 56).value >> 49)).value|\
           u64((u64(x.value << 56).value >> 49)).value|\
           u64((u64(x.value << 56).value >> 49)).value|\
           u64((u64(x.value << 56).value >> 49)).value|\
           u64((u64(x.value << 56).value >> 49)).value)
board = u64(0b0000000100000001000000010000000100000001000000010000000100000001)
print_bitboard(board)
board2 = rotateCW(board)
print()
print_bitboard(board2)
