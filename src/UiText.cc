#include "UiText.hh"

#include <ncurses.h>

#include "Table.hh"

UiText::UiText() {
    init();
}

UiText::~UiText() {
    close();
}

void UiText::init() {
    initscr();
    cbreak();
    noecho();
    timeout(0);
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    if (!has_colors()) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
}

void UiText::draw(const Position& position) const {
    for (int j = 0; j < 4 * 5 + 2; ++j) {
        mvaddch(0, j, HORIZONTAL_BORDER);
        mvaddch(4 + 1, j, HORIZONTAL_BORDER);
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            const int idx = i * 4 + j;
            int number = 0;
            if (position.arr[idx] > 0) {
                number = pow(2, position.arr[idx]);
                mvprintw(i + 1, j * 5 + 1, "%4d", number);
            } else {
                mvprintw(i + 1, j * 5 + 1, "%4s", ".");
            }
            mvaddch(i + 1, 0, VERTICAL_BORDER);
            mvaddch(i + 1, 20 + 1, VERTICAL_BORDER);
        }
    }
    mvprintw(8, 0, "Last move: %5s", game.move_names[position.last_move].c_str());
    mvprintw(6, 0, "Moves: %6d", game.move_index);
    mvprintw(7, 0, "Score: %6d", position.score);
    refresh();
}

void UiText::handle_input() {
    int key = getch();
    flushinp();
    switch (key) {
        case KEY_LEFT:
            handle_left_key();
            break;
        case KEY_RIGHT:
            handle_right_key();
            break;
        case KEY_UP:
            handle_up_key();
            break;
        case KEY_DOWN:
            handle_down_key();
            break;
        case KEY_HOME:
            handle_home_key();
            break;
        case KEY_END:
            handle_end_key();
            break;
        case 'a':
            handle_a_key();
            break;
        case 'm':
            handle_m_key();
            break;
        case 'b':
            handle_b_key();
            break;
        case 'n':
            handle_n_key();
            break;
    }
}

void UiText::end() {
    std::cin.get();
}

void UiText::close() {
    endwin();
}

