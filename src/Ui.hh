#pragma once

#include <memory>

#include "Game.hh"
#include "GameState.hh"

class Table;

class Ui {
    public:
        Ui();
        virtual ~Ui() = default;
        virtual void draw(const Position& position) const = 0;
        virtual void handle_input() = 0;
        virtual void clear_background() const {}
        virtual void end() {}
        void update(/*const float elapsed_time*/);
        void handle_left_key();
        void handle_right_key();
        void handle_up_key();
        void handle_down_key();
        void handle_a_key();
        void handle_m_key();
        void handle_home_key();
        void handle_end_key();
        void handle_b_key();
        void handle_n_key();
        void handle_q_key();

        Game game;
        GameState game_state;
    private:

};

typedef std::shared_ptr<Ui> UiPtr;
