#include "mx_input.h"

char *mx_ush_read_line(t_list *history) {
    char c[5];
    char *line = mx_strnew(PATH_MAX);
    int pos = 0;
    bool esc = 0;

    mx_enable_canon();
    while (read(STDIN_FILENO, &c, 4)) {
        int len = strlen(line);

        if (c[0] == '\n') {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }
        else if (MX_IS_LEFT_ARROW(c) || MX_IS_RIGHT_ARROW(c)
                 || MX_IS_END(c) || MX_IS_HOME(c))
            mx_input_moving(line, &pos, &esc, &c[0]);
        else if (c[0] == 127 || MX_IS_DEL(c) || MX_IS_BS(c) || MX_IS_VT(c))
            mx_clear_part_input(line, &pos, &c[0]);
        else if (MX_IS_ESC(c)) {
            esc = !esc;
        }
        // else if (MX_IS_UP_ARROW(c) || MX_IS_DOWN_ARROW(c)) {
        //     t_history *history = mx_file_to_struct();
        //
        //     line = mx_history_moving(c);
        // }
        else {
            print_regular(line, c[0], &pos);
        }
        memset(c, '\0', 5);

    }
    line = mx_strtrim(line);
    return line;
}
