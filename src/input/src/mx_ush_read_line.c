#include "../inc/mx_input.h"

static void control(char *line, int len, int *pos, char *key) {
    if (key[0] == 127 || MX_IS_DEL(key) || MX_IS_BS(key) || MX_IS_VT(key))
        mx_clear_part_input(line, len, pos, key);
    else if (MX_IS_LEFT_ARROW(key) || MX_IS_RIGHT_ARROW(key)
             || MX_IS_END(key) || MX_IS_HOME(key))
        mx_input_moving(line, pos, key);
}

char *mx_ush_read_line() {
    char key[5];
    char *line = mx_strnew(PATH_MAX);
    int pos = 0;
    struct termios savetty;

    savetty = mx_enable_canon();
    printf(MX_SHELL_PROMPT);
    fflush (NULL);
    while (read(STDIN_FILENO, &key, 4)) {
        int len = strlen(line);

        if (MX_IS_UP_ARROW(key) && pos == 0)
            mx_history_manage(line, &pos, &len, key);
        if (key[0] == '\n' || (key[0] == 3 && len == 0)) {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }
        else if (key[0] > 27 && key[0] < 127)
            mx_print_regular(line, key[0], &pos);
        else
            control(line, len, &pos, key);
        memset(key, '\0', 5);
    }
    mx_disable_canon(savetty);
    return line;
}
