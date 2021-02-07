#pragma once

#include <cstdint>
#include <random>
#include <string>
#include <vector>

#include "Position.hh"
#include "Statistic.hh"
#include "Table.hh"

class Game {
    public:
        Game();
        void init();
        std::vector<Move> generate_possible_moves();
        bool make_one_move();
        void put_new_number();
        void make_move(const Move move);
        bool is_possible_to_move(const Move move) const;
        void insert_into_move_history(const Position& position);
        void clear_stats();

        int64_t move_index;
        Table table;
        std::vector<Position> move_history;
        Statistic stats[4];
        std::string move_names[5];

    private:
        int get_one_or_two();

        std::vector<Move> moves;
        std::random_device rd;
};
