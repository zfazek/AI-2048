#pragma once

#include <cstdint>

struct Statistic {
    uint64_t count;
    uint64_t sum;
    uint64_t max;

    Statistic();
    void clear();
    void update(const uint64_t sum);
};
