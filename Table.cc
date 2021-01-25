#include "Table.hh"

#include <cmath>
#include <iostream>
#include <iomanip>

int Table::get_new_slot_idx() {
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 15);
    int idx;
    while (true) {
        idx = distrib(gen);
        if (arr[idx] == 0) {
            break;
        }
    }
    return idx;
}

Table::Table() {
    init();
}

void Table::init() {
    for (int i = 0; i < 16; i++) {
        arr[i] = 0;
    }
}

Value Table::slide(const uint32_t in) const {
    Value v;
    v.row = 0;
    v.score = 0;
    return v;
}

void Table::make_move(const int idx, const int number) {
    arr[idx] = number;
}

void Table::print() const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            const int idx = i * 4 + j;
            int number = 0;
            if (arr[idx] > 0) {
                number = pow(2, arr[idx]);
            }
            std::cout << std::setw(4) << number << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
