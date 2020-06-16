#include "mx_input.h"

void mx_disable_canon(struct termios savetty) {
    tcsetattr (0, TCSAFLUSH, &savetty);
}
