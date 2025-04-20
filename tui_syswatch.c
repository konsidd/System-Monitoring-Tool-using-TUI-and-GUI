#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "stats_function.h"

void draw_bar(WINDOW *win, int y, const char *label, double percent) {
    int width = 50;
    int filled = (int)(percent / 100.0 * width);
    mvwprintw(win, y, 2, "%s: [", label);
    wattron(win, A_REVERSE);
    for (int i = 0; i < filled; i++) {
        wprintw(win, " ");
    }
    wattroff(win, A_REVERSE);
    for (int i = filled; i < width; i++) {
        wprintw(win, " ");
    }
    wprintw(win, "] %.2f%%", percent);
}

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    
    WINDOW *win = newwin(20, 70, 1, 1);
    box(win, 0, 0);

    double cpu_percent = 0.0;
    double mem_percent = 0.0;

    while (1) {
        werase(win);
        box(win, 0, 0);
        mvwprintw(win, 1, 2, "SysWatch - TUI Mode");

        // Simulated or real CPU/memory usage
        cpu_percent = rand() % 100;     // Replace with real data
        mem_percent = rand() % 100;     // Replace with real data

        draw_bar(win, 3, "CPU Usage", cpu_percent);
        draw_bar(win, 5, "Memory Usage", mem_percent);

        mvwprintw(win, 7, 2, "Press 'q' to quit");
        wrefresh(win);

        int ch = getch();
        if (ch == 'q' || ch == 'Q') break;

        sleep(1);
    }

    endwin();
    return 0;
}