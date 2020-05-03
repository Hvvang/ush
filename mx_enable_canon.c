#include "ush.h"

void set_props(void) {
    struct termios tty;

    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty);
}

// struct termios *mx_get_tty(void) {
//     static struct termios tty;
//
//     return &tty;
// }

void mx_enable_canon(void) {
    static struct termios tty;

    tcgetattr(STDIN_FILENO, &tty);
    setvbuf(stdout, NULL, _IONBF, 0);
    set_props();
}
