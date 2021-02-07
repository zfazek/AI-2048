#include "Statistic.hh"

Statistic::Statistic() {
    clear();
}

void Statistic::clear() {
    count = 0;
    sum = 0;
    max = 0;
}

void Statistic::update(const uint64_t sum) {
    ++count;
    this->sum += sum;
    if (sum > this->max) {
        this->max = sum;
    }
}
