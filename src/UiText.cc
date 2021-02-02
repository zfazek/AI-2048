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

void UiText::draw(const Table& table) const {
    for (int j = 0; j < 4 * 5 + 2; ++j) {
        mvaddch(0, j, HORIZONTAL_BORDER);
        mvaddch(4 + 1, j, HORIZONTAL_BORDER);
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            const int idx = i * 4 + j;
            int number = 0;
            if (table.arr[idx] > 0) {
                number = pow(2, table.arr[idx]);
                mvprintw(i + 1, j * 5 + 1, "%4d", number);
            } else {
                mvprintw(i + 1, j * 5 + 1, "%4s", ".");
            }
            mvaddch(i + 1, 0, VERTICAL_BORDER);
            mvaddch(i + 1, 20 + 1, VERTICAL_BORDER);
        }
    }
    /*
    mvprintw(0, table.WIDTH + 3, "Level: %d", table.get_level());
    mvprintw(1, table.WIDTH + 3, "Lines: %d", table.get_cleared_lines());
    mvprintw(4, table.WIDTH + 3, "Next:");
    */
    mvprintw(6, 0, "Score: %d", table.get_score());
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
        case 'a':
            handle_a_key();
            break;
        case 'm':
            handle_m_key();
            break;
    }
}

void UiText::end() {
    std::cin.get();
}

void UiText::close() {
    endwin();
}

