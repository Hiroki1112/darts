#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include "darts.h"

int add_darts(int x);
int my_mvaddstr(int y, int x, char *str);

int main(int argc, char *argv[]) {
    initscr();
    signal(SIGINT, SIG_IGN);
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    leaveok(stdscr, TRUE);
    scrollok(stdscr, FALSE);

    for (int x = COLS - 1; ; --x) {
        if (add_darts(x) == ERR) break;
        getch();
        refresh();
        usleep(100000);
    }
    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();

    return OK;
}

int my_mvaddstr(int y, int x, char *str) {
    for ( ; x < 0; ++x, ++str)
        if (*str == '\0')  return ERR;
    for ( ; *str != '\0'; ++str, ++x)
        if (mvaddch(y, x, *str) == ERR)  return ERR;
    return OK;
}

int add_darts(int x) {
    static char *darts[DARTS_PATTERNS][DARTS_HEIGHT + 1]
        = {
           {DARTS_BODY_TOP11, DARTS_BODY_TOP12, DARTS_BODY_TOP13,
            DARTS_BODY,
            DARTS_BODY_BTM11, DARTS_BODY_BTM12, DARTS_BODY_BTM13
           },
           {DARTS_BODY_TOP21, DARTS_BODY_TOP22, DARTS_BODY_TOP23,
            DARTS_BODY,
            DARTS_BODY_BTM21, DARTS_BODY_BTM22, DARTS_BODY_BTM23
           },
           {DARTS_BODY_TOP31, DARTS_BODY_TOP32, DARTS_BODY_TOP33,
            DARTS_BODY,
            DARTS_BODY_BTM31, DARTS_BODY_BTM32, DARTS_BODY_BTM33
           },
           {DARTS_BODY_TOP41, DARTS_BODY_TOP42, DARTS_BODY_TOP43,
            DARTS_BODY,
            DARTS_BODY_BTM41, DARTS_BODY_BTM42, DARTS_BODY_BTM43
           },
           {DARTS_BODY_TOP31, DARTS_BODY_TOP32, DARTS_BODY_TOP33,
            DARTS_BODY,
            DARTS_BODY_BTM31, DARTS_BODY_BTM32, DARTS_BODY_BTM33
           },
           {DARTS_BODY_TOP21, DARTS_BODY_TOP22, DARTS_BODY_TOP23,
            DARTS_BODY,
            DARTS_BODY_BTM21, DARTS_BODY_BTM22, DARTS_BODY_BTM23
           }};

    int y, i = 0;

    if (x < - DARTS_LENGTH)  return ERR;
    y = LINES / 2 - 4;

    for (i = 0; i <= DARTS_HEIGHT; ++i) {
        my_mvaddstr(y + i, x, darts[(DARTS_LENGTH + x) % DARTS_PATTERNS][i]);
    }
    return OK;
}
