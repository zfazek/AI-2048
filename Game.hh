#pragma once

#include <cstdint>
#include <random>
#include <unordered_map>

#include "Table.hh"

class Game {
    public:
        Table table;
        void make_move();

    private:
        int get_one_or_two();

        std::unordered_map<uint32_t, Value> dp;
        std::random_device rd;
};
