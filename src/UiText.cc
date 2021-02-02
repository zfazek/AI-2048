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
    timeout(20);
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    if (!has_colors()) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    init_color(1, 0xee, 0xe4, 0xda);
    init_color(2, 0xee, 0xe1, 0xc9);
    init_color(3, 0xf3, 0xb2, 0x7a);
    init_color(4, 0xf6, 0x96, 0x64);
    init_color(5, 0xf7, 0x7c, 0x5f);
    init_color(6, 0xf7, 0x5f, 0x3b);
    init_color(7, 0xed, 0xd0, 0x73);
    init_color(8, 0xed, 0xcc, 0x62);
    init_color(9, 0xed, 0xc9, 0x50);
    init_color(10, 0xed, 0xc5, 0x3f);
    init_color(11, 0xed, 0xc2, 0x2e);
    init_color(12, 0xff, 0xff, 0xff);
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, 1);
    init_pair(3, COLOR_BLACK, 2);
    init_pair(4, COLOR_BLACK, 3);
    init_pair(5, COLOR_BLACK, 4);
    init_pair(6, COLOR_BLACK, 5);
    init_pair(7, COLOR_BLACK, 6);
    init_pair(8, COLOR_BLACK, 7);
    init_pair(9, COLOR_WHITE, 8);
    init_pair(10, COLOR_WHITE, 9);
    init_pair(11, COLOR_WHITE, 10);
    init_pair(12, COLOR_BLACK, 11);
    init_pair(13, COLOR_BLACK, 12);
}

void UiText::draw(const Position& position) const {
    for (int j = 0; j < 4 * 5 + 1; ++j) {
        mvaddch(0, j, HORIZONTAL_BORDER);
        mvaddch(2, j, HORIZONTAL_BORDER);
        mvaddch(4, j, HORIZONTAL_BORDER);
        mvaddch(6, j, HORIZONTAL_BORDER);
        mvaddch(8, j, HORIZONTAL_BORDER);
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            const int idx = i * 4 + j;
            int number = 0;
            if (position.arr[idx] > 0) {
                number = pow(2, position.arr[idx]);
                int color_idx = position.arr[idx] + 1;
                if (color_idx > 13) {
                    color_idx = 13;
                }
                attron(COLOR_PAIR(color_idx));
                mvprintw(i * 2 + 1, j * 5 + 1, "%4d", number);
                attroff(COLOR_PAIR(color_idx));
            } else {
                attron(COLOR_PAIR(1));
                mvprintw(i * 2 + 1, j * 5 + 1, "%4s", " ");
                attroff(COLOR_PAIR(1));
            }
            mvaddch(i * 2, 0, VERTICAL_BORDER);
            mvaddch(i * 2 + 1, 0, VERTICAL_BORDER);
            mvaddch(i * 2 + 2, 0, VERTICAL_BORDER);
            mvaddch(i * 2, 20, VERTICAL_BORDER);
            mvaddch(i * 2 + 1, 20, VERTICAL_BORDER);
            mvaddch(i * 2 + 2, 20, VERTICAL_BORDER);
        }
    }
    mvprintw(9, 0, "Moves: %6d", game.move_index);
    mvprintw(10, 0, "Score: %6d", position.score);
    mvprintw(11, 0, "Last move: %5s", game.move_names[position.last_move].c_str());
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
        case 'q':
            handle_q_key();
            break;
    }
}

void UiText::end() {
}

void UiText::close() {
    endwin();
}

