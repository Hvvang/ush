#ifndef MX_INPUT_H
#define MX_INPUT_H

#include "../../../libmx/inc/libmx.h"
#include "../../history/inc/mx_history.h"

#define MX_SHELL_PROMPT "u$h> "

#define MX_IS_SOH(code)         !strcmp(code, "\001\0")
#define MX_IS_STX(code)         !strcmp(code, "\002\0")
#define MX_IS_ETX(code)         !strcmp(code, "\003\0")
#define MX_IS_EOT(code)         !strcmp(code, "\004\0")
#define MX_IS_ENQ(code)         !strcmp(code, "\005\0")
#define MX_IS_ACK(code)         !strcmp(code, "\006\0")
#define MX_IS_BEL(code)         !strcmp(code, "\007\0")

#define MX_IS_BS(code)          !strcmp(code, "\010\0") || !strcmp(code, "\177\0")
#define MX_IS_HT(code)          !strcmp(code, "\011\0")
#define MX_IS_NL(code)          !strcmp(code, "\012\0")
#define MX_IS_VT(code)          !strcmp(code, "\013\0")

#define MX_IS_NP(code)          !strcmp(code, "\014\0")
#define MX_IS_CR(code)          !strcmp(code, "\015\0")
#define MX_IS_SO(code)          !strcmp(code, "\016\0")
#define MX_IS_SI(code)          !strcmp(code, "\017\0")

#define MX_IS_DLE(code)         !strcmp(code, "\020\0")
#define MX_IS_DC1(code)         !strcmp(code, "\021\0") // Not found
#define MX_IS_DC2(code)         !strcmp(code, "\022\0") // Recurcive search in history TODO
#define MX_IS_DC3(code)         !strcmp(code, "\023\0") // Not found
#define MX_IS_DC4(code)         !strcmp(code, "\024\0")
#define MX_IS_NAK(code)         !strcmp(code, "\025\0")
#define MX_IS_SYN(code)         !strcmp(code, "\026\0") // TODO
#define MX_IS_ETB(code)         !strcmp(code, "\027\0")

#define MX_IS_CAN(code)         !strcmp(code, "\030\0")
#define MX_IS_EM(code)          !strcmp(code, "\031\0")
#define MX_IS_SUB(code)         !strcmp(code, "\032\0")
#define MX_IS_ESC(code)         !strcmp(code, "\033\0")
#define MX_IS_FS(code)          !strcmp(code, "\034\0")
#define MX_IS_GS(code)          !strcmp(code, "\035\0")
#define MX_IS_RS(code)          !strcmp(code, "\036\0")
#define MX_IS_US(code)          !strcmp(code, "\037\0")

#define MX_IS_SP(code)          !strcmp(code, "\040\0")

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


struct termios mx_enable_canon(void);
bool mx_match(char *src, char *regex);
void mx_disable_canon(struct termios savetty);
void mx_clear_input(char *input, int *pos);
void mx_clear_part_input(char *line, int len, int *pos, char *c);
void mx_clear_screen(char *line, int pos);
void mx_get_end(char *str, int *pos);
void mx_get_start(int *pos);
void mx_input_moving(char *line, int *pos, char *c);
void mx_move_left(int *pos);
void mx_move_right(char *str, int *pos);
void mx_print_backspace(char *str, int *pos);
void mx_print_del(char *str, int *pos);
void mx_print_regular(char *str, char *c, int *pos);
void mx_history_manage(char *line, int *pos, int *len, char *key);
char *mx_ush_read_line(char *line);

#endif
