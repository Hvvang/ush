#include "../inc/mx_input.h"

char *mx_ush_read_line() {
    char c[5];
    char *line = mx_strnew(PATH_MAX);
    int pos = 0;
    bool esc = false;

    mx_enable_canon();
    while (read(STDIN_FILENO, &c, 4)) {
        int len = strlen(line);

        // printf("c[0] = %c c[1] = %c c[2] = %c c[3] = %c c[4] = %c\n", c[0], c[1], c[2], c[3], c[4]);
        if (c[0] == '\n') {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }
        else if (c[0] == 127 || MX_IS_DEL(c) || MX_IS_BS(c) || MX_IS_VT(c))
            mx_clear_part_input(line, len, &pos, &c[0]);
        else if (MX_IS_LEFT_ARROW(c) || MX_IS_RIGHT_ARROW(c)
                 || MX_IS_END(c) || MX_IS_HOME(c))
            mx_input_moving(line, &pos, &esc, &c[0]);
        else if (MX_IS_ESC(c)) {
            esc = !esc;
        }
        else if (MX_IS_UP_ARROW(c) || MX_IS_DOWN_ARROW(c)) {
            t_history *history = mx_file_to_struct();

            // line = mx_history_moving(history, c);
            mx_clear_input(line, &pos);
            printf("%s", history->command);
            pos += strlen(history->command);
        }
        else {
            mx_print_regular(line, c[0], &pos);
        }
        memset(c, '\0', 5);
    }
    // mx_disable_canon();
    return line;
}
