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
    timeout(-1);
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    if (!has_colors()) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_BLACK, COLOR_BLUE);
    init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(7, COLOR_BLACK, COLOR_CYAN);
    init_pair(8, COLOR_WHITE, COLOR_RED);
    init_pair(9, COLOR_WHITE, COLOR_GREEN);
    init_pair(10, COLOR_WHITE, COLOR_YELLOW);
    init_pair(11, COLOR_WHITE, COLOR_BLUE);
    init_pair(12, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(13, COLOR_WHITE, COLOR_CYAN);
    init_pair(99, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_BLACK);
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
                const int max_color = 13;
                if (color_idx > max_color) {
                    color_idx = max_color;
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
    mvprintw(9, 0, "Moves:    %6d", game.move_index);
    mvprintw(10, 0, "Score:    %6d", position.score);
    mvprintw(11, 0, "Last move:  %5s", game.move_names[position.last_move].c_str());
    draw_help();
    draw_stat(UP, 27, 0);
    draw_stat(LEFT, 47, 0);
    draw_stat(RIGHT, 67, 0);
    draw_stat(DOWN, 87, 0);
    refresh();
}

void UiText::draw_help() const {
    mvprintw(13, 0, "ARROW KEYS: move");
    mvprintw(14, 0, "'b':        undo last move");
    mvprintw(15, 0, "'n':        redo last move");
    mvprintw(16, 0, "HOME:       undo all moves");
    mvprintw(17, 0, "END:        redo all moves");
    mvprintw(18, 0, "'m':        AI moves once");
    mvprintw(19, 0, "'a':        Toggle AI mode");
    mvprintw(20, 0, "'q':        Quit");
}

void UiText::draw_stat(const Move move, const int pos_x, const int pos_y) const {
    const Statistic statistic = game.stats[move];
    mvprintw(pos_y, pos_x, "%5s", game.move_names[move].c_str());
    mvprintw(pos_y + 1, pos_x, "count:   %5d", statistic.count);
    mvprintw(pos_y + 2, pos_x, "average: %5d", statistic.count == 0 ?
            0 : statistic.sum / statistic.count);
    mvprintw(pos_y + 3, pos_x, "max:     %5d", statistic.max);
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

