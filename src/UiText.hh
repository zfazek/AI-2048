#pragma once

#include "Ui.hh"

class UiText : public Ui {
    public:
        UiText();
        ~UiText() override;
        void draw(const Position& position) const override;
        void handle_input() override;
        void end() override;

    private:
        void init();
        void close();
        void draw_help() const;
        void draw_stat(const Move move, const int pos_x, const int pos_y) const;

        static constexpr char VERTICAL_BORDER = ' ';
        static constexpr char HORIZONTAL_BORDER = ' ';
};
