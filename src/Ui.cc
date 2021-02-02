#include "Ui.hh"

Ui::Ui() {
    game_state = GameState::GAME;
}

void Ui::handle_left_key() {
    if (game_state == GameState::GAME) {
        game.make_move(LEFT);
        game.put_new_number();
    }
}

void Ui::handle_right_key() {
    if (game_state == GameState::GAME) {
        game.make_move(RIGHT);
        game.put_new_number();
    }
}

void Ui::handle_up_key() {
    if (game_state == GameState::GAME) {
        game.make_move(UP);
        game.put_new_number();
    }
}

void Ui::handle_down_key() {
    if (game_state == GameState::GAME) {
        game.make_move(DOWN);
        game.put_new_number();
    }
}

void Ui::handle_a_key() {
    if (game_state == GameState::GAME) {
        game_state= GameState::AI;
    } else if (game_state == GameState::AI) {
        game_state = GameState::GAME;
    }
}

void Ui::handle_m_key() {
    if (game_state == GameState::GAME) {
        game.make_one_move();
    }
}

void Ui::update(/*const float elapsed_time*/) {
    if (game_state == GameState::AI) {
        const bool succ = game.make_one_move();
        if (!succ) {
            game_state = GameState::QUIT;
        }
    }
}
