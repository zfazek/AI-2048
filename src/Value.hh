#pragma once

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <ostream>

struct Value {
    uint32_t row;
    uint32_t score;
    friend bool operator==(const Value& lhs, const Value& rhs) {
        return lhs.row == rhs.row && lhs.score == rhs.score;
    }
    friend std::ostream& operator<<(std::ostream& os, const Value& v) {
        os << "0x" << std::setfill('0') << std::setw(8) << std::right << std::hex
           << v.row << std::dec << " " << v.score;
        return os;
    }
};

