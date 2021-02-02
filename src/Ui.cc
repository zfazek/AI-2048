#include "Ui.hh"

Ui::Ui() {
    game_state = GameState::GAME;
    game.init();
}

void Ui::handle_left_key() {
    if (game_state == GameState::GAME &&
            game.is_possible_to_move(LEFT)) {
        game.make_move(LEFT);
        game.put_new_number();
        game.insert_into_move_history(game.table.position);
    }
}

void Ui::handle_right_key() {
    if (game_state == GameState::GAME &&
            game.is_possible_to_move(RIGHT)) {
        game.make_move(RIGHT);
        game.put_new_number();
        game.insert_into_move_history(game.table.position);
    }
}

void Ui::handle_up_key() {
    if (game_state == GameState::GAME &&
            game.is_possible_to_move(UP)) {
        game.make_move(UP);
        game.put_new_number();
        game.insert_into_move_history(game.table.position);
    }
}

void Ui::handle_down_key() {
    if (game_state == GameState::GAME &&
            game.is_possible_to_move(DOWN)) {
        game.make_move(DOWN);
        game.put_new_number();
        game.insert_into_move_history(game.table.position);
    }
}

void Ui::handle_a_key() {
    if (game_state == GameState::GAME) {
        game_state = GameState::AI;
    } else if (game_state == GameState::AI) {
        game_state = GameState::GAME;
    }
}

void Ui::handle_m_key() {
    if (game_state == GameState::GAME) {
        game.make_one_move();
    }
}

void Ui::handle_home_key() {
    game.move_index = 0;
    game.table.position = game.move_history[game.move_index];
}

void Ui::handle_end_key() {
    game.move_index = game.move_history.size() - 1;
    game.table.position = game.move_history[game.move_index];
}

void Ui::handle_b_key() {
    if (game.move_index > 0) {
        --game.move_index;
        game.table.position = game.move_history[game.move_index];
    }
}

void Ui::handle_n_key() {
    if (game.move_index < static_cast<int64_t>(game.move_history.size() - 1)) {
        ++game.move_index;
        game.table.position = game.move_history[game.move_index];
    }
}

void Ui::handle_q_key() {
    game_state = GameState::QUIT;
}

void Ui::update(/*const float elapsed_time*/) {
    if (game_state == GameState::AI) {
        const bool succ = game.make_one_move();
        if (!succ) {
            game_state = GameState::GAME;
        }
    }
}
