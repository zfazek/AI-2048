#include <iostream>

#include "Game.hh"

int main() {
    Game game;
    game.put_new_number();
    game.put_new_number();
    while (true) {
        game.table.print();
        const bool succ = game.make_one_move();
        if (!succ) {
            break;
        }
    }
}
