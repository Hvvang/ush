#include "../inc/mx_input.h"

void mx_disable_canon(void) {
    struct termios tty;

    tcsetattr(STDIN_FILENO, TCSADRAIN, &tty);
}
