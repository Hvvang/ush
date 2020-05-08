#ifndef MX_INPUT_H
#define MX_INPUT_H

#include "../../../inc/mx_posix.h"
#include "../../history/inc/mx_history.h"
#include "../../../libmx/inc/libmx.h"

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
#define MX_IS_HOME(code)        !strcmp(code, "\033[H\0")
#define MX_IS_END(code)         !strcmp(code, "\033[F\0")
#define MX_IS_PgUp(code)        !strcmp(code, "\033[I\0")
#define MX_IS_PgDn(code)        !strcmp(code, "\033[G\0")

void mx_enable_canon(void);
void mx_disable_canon(void);
void mx_clear_input(char *input, int *pos);
void mx_clear_part_input(char *line, int len, int *pos, char *c);
void mx_get_end(char *str, int *pos, bool *esc);
void mx_get_start(int *pos, bool *esc);
void mx_input_moving(char *line, int *pos, bool *esc, char *c);
void mx_move_left(int *pos);
void mx_move_right(char *str, int *pos);
void mx_print_backspace(char *str, int *pos);
void mx_print_del(char *str, int *pos);
void mx_print_regular(char *str, char c, int *pos);
char *mx_ush_read_line();

#endif
