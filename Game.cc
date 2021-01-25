#include "Game.hh"

void Game::make_move() {
    const int idx = table.get_new_slot_idx();
    const int new_number = get_one_or_two();
    table.make_move(idx, new_number);
}

int Game::get_one_or_two() {
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(0.0, 1.0);
    const float number = distrib(gen);
    if (number < 0.9) {
        return 1;
    } else {
        return 2;
    }
}
