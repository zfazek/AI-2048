#pragma once

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <random>
#include <unordered_map>

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

class Table {
    public:
        Table();

        void init();
        void make_move(const int idx1, const int idx2, const int idx3, const int idx4);
        int get_new_slot_idx();
        void put_new_number(const int idx, const int number);
        Value slide(const uint32_t in) const;
        bool is_changing(const int idx1, const int idx2, const int idx3, const int idx4) const;
        bool is_end() const;
        void print() const;

        //  0  1  2  3
        //  4  5  6  7
        //  8  9 10 11
        // 12 13 14 15
        uint8_t arr[16];
        uint32_t score;

    private:
        std::unordered_map<uint32_t, Value> dp;
        std::random_device rd;

};
