#include "mx_input.h"

struct termios mx_enable_canon(void) {
    struct termios savetty;
    struct termios tty;

    tcgetattr (0, &tty);
    savetty = tty;
    tty.c_lflag &= ~(ICANON | ECHO | ISIG | BRKINT | ICRNL
                    | INPCK | ISTRIP | IXON | OPOST | IEXTEN);
    tty.c_cflag |= (CS8);
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &tty);
    setvbuf(stdout, NULL, _IONBF, 0);
    return savetty;
}
