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

        static constexpr char VERTICAL_BORDER = ' ';
        static constexpr char HORIZONTAL_BORDER = ' ';
};
