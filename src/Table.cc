#include "Table.hh"

#include <cmath>
#include <iomanip>
#include <iostream>

int Table::get_new_slot_idx() {
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 15);
    int idx;
    while (true) {
        idx = distrib(gen);
        if (position.arr[idx] == 0) {
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
        position.arr[i] = 0;
    }
    position.score = 0;
    position.last_move = NONE;
}

void Table::make_move(
        const int idx1,
        const int idx2,
        const int idx3,
        const int idx4) {
    const uint8_t v1 = position.arr[idx1];
    const uint8_t v2 = position.arr[idx2];
    const uint8_t v3 = position.arr[idx3];
    const uint8_t v4 = position.arr[idx4];
    const uint32_t key = v1 * 16777216 + v2 * 65536 + v3 * 256 + v4;
    Value v;
    if (dp.find(key) != dp.end()) {
        v = dp.at(key);
    } else {
        v = slide(key);
        dp[key] = v;
    }
    position.score += v.score;
    static uint8_t r[4];
    r[3] = v.row & 0xff;
    r[2] = (v.row >> 8) & 0xff;
    r[1] = (v.row >> 16) & 0xff;
    r[0] = (v.row >> 24) & 0xff;
    position.arr[idx1] = r[0];
    position.arr[idx2] = r[1];
    position.arr[idx3] = r[2];
    position.arr[idx4] = r[3];
}

Value Table::slide(const uint32_t in) const {
    Value v = {0, 0};
    static uint8_t r[4];
    r[3] = in & 0xff;
    r[2] = (in >> 8) & 0xff;
    r[1] = (in >> 16) & 0xff;
    r[0] = (in >> 24) & 0xff;
    for (int i = 3; i >= 1; --i) {
        if (r[i] == 0) continue;
        for (int j = i - 1; j >= 0; --j) {
            if (r[j] == 0) continue;
            if (r[i] != r[j]) break;
            ++r[i];
            v.score += pow(2, r[i]);
            r[j] = 0;
            break;
        }
    }
    for (int i = 2; i >= 0; --i) {
        for (int j = i + 1; j < 4; ++j) {
            if (r[j] == 0) {
                r[j] = r[j - 1];
                r[j - 1] = 0;
            } else {
                break;
            }
        }
    }
    v.row = r[0] * 16777216 + r[1] * 65536 + r[2] * 256 + r[3];
    return v;
}

void Table::put_new_number(const int idx, const int number) {
    position.arr[idx] = number;
}

uint64_t Table::get_score() const {
    return position.score;
}

bool Table::is_possible_to_slide(const int idx1, const int idx2, const int idx3, const int idx4) const {
    const uint8_t v1 = position.arr[idx1];
    const uint8_t v2 = position.arr[idx2];
    const uint8_t v3 = position.arr[idx3];
    const uint8_t v4 = position.arr[idx4];
    if (v1 == 0 && v2 == 0 && v3 == 0 && v4 == 0) return false;
    if (v1 > 0 && v1 == v2) return true;
    if (v2 > 0 && v2 == v3) return true;
    if (v3 > 0 && v3 == v4) return true;
    if (v4 == 0) return true;
    if (v3 == 0 && (v2 > 0 || v1 > 0)) return true;
    if (v2 == 0 && v1 > 0) return true;
    return false;
}

bool Table::is_changing(const int idx1, const int idx2, const int idx3, const int idx4) const {
    const uint8_t v1 = position.arr[idx1];
    const uint8_t v2 = position.arr[idx2];
    const uint8_t v3 = position.arr[idx3];
    const uint8_t v4 = position.arr[idx4];
    if (v1 == 0 || v2 == 0 || v3 == 0 || v4 == 0) return true;
    if (v1 == v2 || v2 == v3 || v3 == v4) return true;
    return false;
}
