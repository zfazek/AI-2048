#pragma once

#include <memory>

#include "Game.hh"
#include "Ui.hh"

template <class Ui>
void main_common() {
    UiPtr gui = std::make_shared<Ui>();
    gui->game.put_new_number();
    gui->game.put_new_number();
    while (gui->game_state != GameState::QUIT) {
        gui->clear_background();
        gui->handle_input();
        gui->update();
        gui->draw(gui->game.table);
    }
    gui->end();
}
