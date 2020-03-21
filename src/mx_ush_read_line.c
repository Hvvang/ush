#include "ush.h"

#define MX_IS_BS(code)          !strcmp(code, "\010\0")
#define MX_IS_VT(code)          !strcmp(code, "\013\0")
#define MX_IS_ESC(code)         !strcmp(code, "\033\0")
// #define MX_IS_COPY(code)        !strcmp(code, "\037103\0")
// #define MX_IS_PASTE(code)       !strcmp(code, "\037126\0")
#define MX_IS_DEL(code)         !strcmp(code, "\033[3~\0")
#define MX_IS_UP_ARROW(code)    !strcmp(code, "\033[A\0")
#define MX_IS_DOWN_ARROW(code)  !strcmp(code, "\033[B\0")
#define MX_IS_RIGHT_ARROW(code) !strcmp(code, "\033[C\0")
#define MX_IS_LEFT_ARROW(code)  !strcmp(code, "\033[D\0")
#define MX_IS_HOME(code)        !strcmp(code, "\033OH\0")
#define MX_IS_END(code)         !strcmp(code, "\033OF\0")
#define MX_IS_PgUp(code)        !strcmp(code, "\033[I\0")
#define MX_IS_PgDn(code)        !strcmp(code, "\033[G\0")


static void print_regular(char *str, char c, int *pos) {
    mx_insert_char_to_str(str, c, *pos);

    printf("%s", str + (*pos));
    for (int i = 0; i < strlen(str + (*pos)); i++)
        printf("\b");
    printf("%c", c);
    // if (((strlen(len) + 7) % tgetnum("co")) == 0)
    //     printf("\n");
    fflush(stdout);
    *pos = (*pos) + 1;
}

static void print_backspace(char *str, int *pos) {
    if (*pos > 0) {
        mx_del_char_in_str(str, *pos - 1);
        printf("\b%s ", str + (*pos) - 1);
        for (int i = 0; i <= strlen(str + (*pos) - 1); i++)
            printf("\b");
        fflush(NULL);
        *pos = (*pos) - 1;
    }
}

static void get_prev(int *pos) {
    if ((*pos) > 0) {
        printf("\b");
        *pos = (*pos) - 1;
    }
    fflush(NULL);
}

static void get_next(char *str, int *pos) {
    int len = strlen(str);

    if ((*pos) < len) {
        printf("%c", str[*pos]);
        *pos = (*pos) + 1;
    }
    fflush(NULL);
}

static void print_del(char *str, int *pos) {
    mx_del_char_in_str(str, *pos);
    int i = strlen(str);

    printf("%s ", &str[*pos]);
    // for (; i < len; i++)
    //     printf("%c", str[i]);
    // printf(" ");
    while (i >= *pos) {
        i--;
        printf("\b");
    }
    fflush(NULL);
}

static void get_home(int *pos, bool *esc) {
    while (*pos > 0)
        get_prev(pos);
    *esc = false;
}

static void get_end(char *str, int *pos, bool *esc) {
    int len = strlen(str);

    while (*pos < len)
        get_next(str, pos);
    *esc = false;
}

static void clear_input(char *input, int *pos) {
    int len = strlen(input);

    while (*pos > 0) {
        printf("\b");
        *pos = *pos - 1;
    }
    memset(input, ' ', len);
    printf("%s", input);
    memset(input, '\b', len);
    printf("%s", input);
    memset(input, '\0', len);
    fflush(NULL);
}

static t_list *create_copy(t_list *history) {
    t_list *temp = history;
    t_list *copy = NULL;

    while (temp) {
        mx_push_back(&copy, temp->data);
        temp = temp->next;
    }
    return copy;
}

char *mx_ush_read_line(t_list *history) {
    char c[5];
    char *line = mx_strnew(PATH_MAX);
    int pos = 0;

    bool esc = 0;
    bool up = 0;
    bool down = 0;

    t_list *next = create_copy(history);
    t_list *prev = NULL;

    mx_enable_canon();
    while (read(STDIN_FILENO, &c, 4)) {
        // printf("c[0] = %c, c[1] = %c, c[2] = %c c[3] = %c c[4] = %c ",c[0], c[1], c[2], c[3], c[4]);
        // exit(1);
        int len = strlen(line);

        if (c[0] == '\t') {
            continue;
        }
        else if (c[0] == '\n') {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }
        else if (c[0] == 127) {
            print_backspace(line, &pos);
        }
        else if (MX_IS_ESC(c)) {
            esc = !esc;
        }
        else if (MX_IS_LEFT_ARROW(c)) {
            if (!esc)
                get_prev(&pos);
            else
                get_home(&pos, &esc);
        }
        else if (MX_IS_RIGHT_ARROW(c)) {
            if (!esc)
                get_next(line, &pos);
            else
                get_end(line, &pos, &esc);
        }
        else if (MX_IS_UP_ARROW(c)) {
            if (next) {
                if (down) {
                    mx_push_front(&prev, strdup(next->data));
                    mx_pop_front(&next);
                    up = true;
                    down = false;
                }
                if (next) {
                    clear_input(line, &pos);
                    printf("%s", next->data);
                    pos = strlen(next->data);
                    mx_push_front(&prev, strdup(next->data));
                    line = strdup(next->data);
                    mx_pop_front(&next);
                    up = true;
                }
            }
        }
        else if (MX_IS_DOWN_ARROW(c)) {
            if (prev) {
                if (up) {
                    mx_push_front(&next, strdup(prev->data));
                    mx_pop_front(&prev);
                    up = false;
                    down = true;
                }
                if (prev) {
                    clear_input(line, &pos);
                    printf("%s", prev->data);
                    pos = strlen(prev->data);
                    mx_push_front(&next, strdup(prev->data));
                    line = strdup(prev->data);
                    mx_pop_front(&prev);
                    down = true;
                }
            }
            else
                clear_input(line, &pos);
        }
        else if (MX_IS_DEL(c)) {
            if (pos < len)
                print_del(line, &pos);
            else
                printf("\a");
        }
        else if (MX_IS_BS(c)) {
            while (pos > 0)
                print_backspace(line, &pos);
        }
        else if (MX_IS_VT(c)) {
            int len = strlen(line);

            while (pos < len) {
                print_del(line, &pos);
                len = strlen(line);
            }

        }
        else if (MX_IS_END(c)) {
            get_end(line, &pos, &esc);
        }
        else if (MX_IS_HOME(c)) {
            get_home(&pos, &esc);
        }
        // else if (MX_IS_COPY(c)) {
        //     printf("COPY");
        // }
        // else if (MX_IS_PASTE(c)) {
        //     printf("PASTE");
        // }
        else {
            print_regular(line, c[0], &pos);
        }
        memset(c, '\0', 5);

    }
    line = mx_strtrim(line);
    return line;
}
