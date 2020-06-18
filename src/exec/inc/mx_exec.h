#ifndef MX_EXEC_H
#define MX_EXEC_H

#include "../../../inc/mx_posix.h"
#include "../../parser/inc/mx_parser.h"
#include "../../shell/inc/mx_shell.h"


#define MX_W_INT(m) (*(int*) & (m))
#define MX_WSTOPSIG(m) (MX_W_INT(m) >> 8)
#define MX_WSTATUS(m) (MX_W_INT(m) & 0177)
#define MX_WIFSTOPPED(m) (MX_WSTATUS(m) == _WSTOPPED && MX_WSTOPSIG(m) != 0x13)
#define MX_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#define MX_WAIT_TO_INT(m) (*(int *) & (m))
#define MX_WEXITSTATUS(x) ((MX_WAIT_TO_INT(x) >> 8) & 0x000000ff)


void mx_activate_signals(void);
void mx_clear_process(t_processes **prcs, void *kill);
void mx_continue_process(t_processes **processes, t_processes *current, pid_t pid);
char *mx_get_path_to_bin(char *programm_name);
int mx_get_processes_num(t_processes **process);
int mx_launch_process(t_command *command, t_processes **processes, char *path, char **env);
void mx_stop_signals(void);
void mx_push_process(t_processes **processes, char **command, pid_t pid);
void mx_set_term_assoc(pid_t pid);
void mx_suspend_process(char **args, t_processes **processes, pid_t pid);
void print_suspended(char **args, pid_t pid, int suspended_index);

void print_process(t_processes **processes);

#endif
