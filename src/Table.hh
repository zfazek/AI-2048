#pragma once

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <random>
#include <unordered_map>

#include "Position.hh"
#include "Value.hh"

class Table {
    public:
        Table();

        void init();
        void make_move(const int idx1, const int idx2, const int idx3, const int idx4);
        int get_new_slot_idx();
        void put_new_number(const int idx, const int number);
        Value slide(const uint32_t in) const;
        bool is_possible_to_slide(const int idx1, const int idx2, const int idx3, const int idx4) const;
        bool is_changing(const int idx1, const int idx2, const int idx3, const int idx4) const;
        uint64_t get_score() const;

        Position position;
    private:
        std::unordered_map<uint32_t, Value> dp;
        std::random_device rd;

};
