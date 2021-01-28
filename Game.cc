#include "Game.hh"
#include <chrono>

Game::Game() {
    move_names[0] = "UP";
    move_names[1] = "RIGHT";
    move_names[2] = "DOWN";
    move_names[3] = "LEFT";
}

bool Game::make_one_move() {
    std::vector<Move> moves = generate_possible_moves();
    if (moves.empty()) {
        return false;
    }
    uint8_t arr_orig[16];
    Move best_move = 0;
    uint32_t best_score = 0;
    auto const start = std::chrono::system_clock::now();
    table.counter = 0;
    while (true) {
        for (int i = 0; i < 16; ++i) {
            arr_orig[i] = table.arr[i];
        }
        uint32_t score_orig = table.score;
        for (const Move first_move : moves) {
//            table.print();
//            std::cout << "first move: " << move_names[first_move] << std::endl;
            make_move(first_move);
            put_new_number();
            while (true) {
                std::vector<Move> moves = generate_possible_moves();
                if (moves.empty()) break;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> distrib(0, moves.size() - 1);
                const int idx = distrib(gen);
                make_move(moves[idx]);
                put_new_number();
            }
//            table.print();
            ++table.counter;
            if (table.score > best_score) {
                best_score = table.score;
                best_move = first_move;
            }
            table.score = score_orig;
            for (int i = 0; i < 16; ++i) {
                table.arr[i] = arr_orig[i];
            }
        }
        auto const now = std::chrono::system_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() > 200) {
            break;
        }
    }
    std::cout << "best move: " << move_names[best_move] << ", best_score: " << best_score << std::endl;
    make_move(best_move);
    put_new_number();
    return true;
}

std::vector<Move> Game::generate_possible_moves() const {
    std::vector<Move> moves;
    if (table.is_changing(0, 4, 8, 12) ||
            table.is_changing(1, 5, 9, 13) ||
            table.is_changing(2, 6, 10, 14) ||
            table.is_changing(3, 7, 11, 15)) {
        moves.push_back(UP);
        moves.push_back(DOWN);
    }
    if (table.is_changing(0, 1, 2, 3) ||
            table.is_changing(4, 5, 6, 7) ||
            table.is_changing(8, 9, 10, 11) ||
            table.is_changing(12, 13, 14, 15)) {
        moves.push_back(RIGHT);
        moves.push_back(LEFT);
    }
    return moves;
}

void Game::make_move(const Move move) {
    switch (move) {
        case UP:
            table.make_move(12, 8, 4, 0);
            table.make_move(13, 9, 5, 1);
            table.make_move(14, 10, 6, 2);
            table.make_move(15, 11, 7, 3);
            break;
        case RIGHT:
            table.make_move(0, 1, 2, 3);
            table.make_move(4, 5, 6, 7);
            table.make_move(8, 9, 10, 11);
            table.make_move(12, 13, 14, 15);
            break;
        case DOWN:
            table.make_move(0, 4, 8, 12);
            table.make_move(1, 5, 9, 13);
            table.make_move(2, 6, 10, 14);
            table.make_move(3, 7, 11, 15);
            break;
        case LEFT:
            table.make_move(3, 2, 1, 0);
            table.make_move(7, 6, 5, 4);
            table.make_move(11, 10, 9, 8);
            table.make_move(15, 14, 13, 12);
            break;
    }
}

void Game::put_new_number() {
    const int idx = table.get_new_slot_idx();
    const int new_number = get_one_or_two();
    table.put_new_number(idx, new_number);
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
