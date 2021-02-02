#pragma once

#include <cstdint>

typedef int Move;
constexpr Move UP = 0;
constexpr Move RIGHT = 1;
constexpr Move DOWN = 2;
constexpr Move LEFT = 3;
constexpr Move NONE = 4;

struct Position {
        //  0  1  2  3
        //  4  5  6  7
        //  8  9 10 11
        // 12 13 14 15
    uint8_t arr[16];
    uint64_t score;
    Move last_move;
};
