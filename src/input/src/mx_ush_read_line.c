#include "mx_input.h"


#define MX_MOVING(code) (MX_IS_SOH(code) || MX_IS_HOME(code) ||\
                         MX_IS_STX(code) || MX_IS_LEFT_ARROW(code) ||\
                         MX_IS_ENQ(code) || MX_IS_END(code) ||\
                         MX_IS_ACK(code) || MX_IS_RIGHT_ARROW(code))

#define MX_CLEARING(code) (MX_IS_EOT(code) || MX_IS_NAK(code)||\
                         MX_IS_BS(code) || MX_IS_US(code) ||\
                         MX_IS_VT(code) || MX_IS_NP(code) ||\
                         MX_IS_ETB(code))

#define MX_OPTINS(code) (MX_IS_HT(code) || MX_IS_SUB(code)||\
                         MX_IS_DC4(code) || MX_IS_SP(code))

#define MX_STOP(code) (MX_IS_ETX(code) || MX_IS_CAN(code)||\
                       MX_IS_BEL(code) || MX_IS_NL(code) ||\
                       MX_IS_SO(code) || MX_IS_SI(code))

static void stop_input(char *line, char *key) {
    if (MX_IS_ETX(key) || MX_IS_CAN(key)) {
        memset(line, '\0', PATH_MAX);
        write(STDOUT_FILENO, "\n", 1);
    }
    else if (MX_IS_BEL(key)) {
        memset(line, '\0', PATH_MAX);
        printf("%s", key);
        write(STDOUT_FILENO, "\n", 1);
    }
    else if (MX_IS_NL(key) || MX_IS_SO(key) || MX_IS_SI(key)) {
        write(STDOUT_FILENO, "\n", 1);
    }
}

static void clearing(char *line, char *key, int *pos, int *status) {
    if (MX_IS_EOT(key)) {
        if (strlen(line))
            mx_print_del(line, pos);
        else {
            *status = 666;
            return;
        }
    }
    if (MX_IS_NAK(key))
        mx_clear_input(line, pos);
    if (MX_IS_BS(key) || MX_IS_US(key))
        mx_print_backspace(line, pos);
    if (MX_IS_VT(key))
        while (*pos < (int)strlen(line))
            mx_print_del(line, pos);
    if (MX_IS_NP(key))
        mx_clear_screen(line, *pos);
    if (MX_IS_ETB(key))
        while (*pos > 0)
            mx_print_backspace(line, pos);
}

static void moving(char *line, char *key, int *pos) {
    if (MX_IS_SOH(key) || MX_IS_HOME(key))
        mx_get_start(pos);
    if (MX_IS_STX(key) || MX_IS_LEFT_ARROW(key))
        mx_move_left(pos);
    if (MX_IS_ENQ(key) || MX_IS_END(key))
        mx_get_end(line, pos);
    if (MX_IS_ACK(key) || MX_IS_RIGHT_ARROW(key))
        mx_move_right(line, pos);
}

static void options(char *line, char *key, int *pos) {
    if (MX_IS_HT(key))
        mx_print_regular(line, "    ", pos);
    else if (MX_IS_SUB(key))
        printf("\a");
    else if (MX_IS_SP(key))
        mx_print_regular(line, " ", pos);
    else if (MX_IS_DC4(key)) {
        if (*pos > 1) {
            int temp = *pos;
            char *str = strdup(line);

            mx_swap_char(&line[temp - 2], &line[temp - 1]);
            mx_clear_input(str, &temp);
            mx_strdel(&str);
            temp = *pos;
            printf("%s", line);
            while (temp < (int)strlen(line)) {
                printf("\b");
                temp++;
            }
        }
    }
}

char *mx_ush_read_line(char *line, int *status) {
    char key[PATH_MAX] = "\0";
    int pos = 0;

    while (*status != 666 && (read(STDIN_FILENO, &key, PATH_MAX))) {
        int len = strlen(line);

        if ((MX_IS_UP_ARROW(key) && pos == 0) || MX_IS_DLE(key))
            mx_history_manage(line, &pos, &len, key);
        if ((mx_match(key, "^[!-~]")) || MX_IS_EM(key))
            mx_print_regular(line, key, &pos);
        else if (MX_MOVING(key))
            moving(line, key, &pos);
        else if (MX_CLEARING(key))
            clearing(line, key, &pos, status);
        else if (MX_OPTINS(key))
            options(line, key, &pos);
        else if (MX_STOP(key)){
            stop_input(line, key);
            break;
        }
        memset(key, '\0', PATH_MAX);
    }
    return line;
}
