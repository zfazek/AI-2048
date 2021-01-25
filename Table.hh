#pragma once

#include <cstdint>
#include <random>

struct Value {
    uint32_t row;
    uint32_t score;
};

class Table {
    public:
        Table();

        void init();
        int get_new_slot_idx();
        void make_move(const int idx, const int number);
        Value slide(const uint32_t in) const;
        void print() const;

        uint8_t arr[16];

    private:
        std::random_device rd;

};
