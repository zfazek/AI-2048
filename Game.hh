#pragma once

#include <cstdint>
#include <random>
#include <string>
#include <vector>

#include "Table.hh"

typedef int Move;
constexpr Move UP = 0;
constexpr Move RIGHT = 1;
constexpr Move DOWN = 2;
constexpr Move LEFT = 3;


class Game {
    public:
        Game();
        std::vector<Move> generate_possible_moves() const;
        bool make_one_move();
        void put_new_number();
        void make_move(const Move move);

        Table table;

    private:
        int get_one_or_two();

        std::string move_names[4];
        std::random_device rd;
};
