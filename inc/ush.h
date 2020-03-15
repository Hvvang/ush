#ifndef USH_H
#define USH_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <wchar.h>
#include <fcntl.h>
#include <malloc.h>
#include <dirent.h>
#include "libmx/inc/libmx.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <pwd.h>
#include <grp.h>

//------ POSIX C lib------
#include <aio.h>         // Asynchronous input and output
#include <arpa/inet.h>   // Functions for manipulating numeric IP addresses (part of Berkeley sockets)
#include <assert.h>      // Verify assumptions
#include <complex.h>     // Complex Arithmetic, see C mathematical functions
#include <cpio.h>        // Magic numbers for the cpio archive format
#include <ctype.h>       // Character types
#include <dirent.h>      // Allows the opening and listing of directories
#include <dlfcn.h>       // Dynamic linking
#include <errno.h>       // Retrieving Error Number
#include <fcntl.h>       // File opening, locking and other operations
#include <fenv.h>        // Floating-Point Environment (FPE), see C mathematical functions
#include <float.h>       // Floating-point types, see C data types
#include <fmtmsg.h>      // Message display structures
#include <fnmatch.h>     // Filename matching
#include <ftw.h>         // File tree traversal
#include <glob.h>        // Pathname "globbing" (pattern-matching)
#include <grp.h>         // User group information and control
#include <iconv.h>       // Codeset conversion facility
#include <inttypes.h>    // Fixed sized integer types, see C data types
#include <iso646.h>      // Alternative spellings, see C alternative tokens
#include <langinfo.h>    // Language information constants – builds on C localization functions
#include <libgen.h>      // Pathname manipulation
#include <limits.h>      // Implementation-defined constants, see C data types
#include <locale.h>      // Category macros, see C localization functions
#include <math.h>        // Mathematical declarations, see C mathematical functions
#include <monetary.h>    // String formatting of monetary units
//#include <mqueue.h>      // Message queue
// #include <ndbm.h>        // NDBM database operations
#include <net/if.h>      // Listing of local network interfaces
#include <netdb.h>       // Translating protocol and host names into numeric addresses (part of Berkeley sockets)
#include <netinet/in.h>  // Defines Internet protocol and address family (part of Berkeley sockets)
#include <netinet/tcp.h> // Additional TCP control options (part of Berkeley sockets)
#include <nl_types.h>    // Localization message catalog functions
#include <poll.h>        // Asynchronous file descriptor multiplexing
#include <pthread.h>     // Defines an API for creating and manipulating POSIX threads
#include <pwd.h>         // passwd (user information) access and control
#include <regex.h>       // Regular expression matching
#include <sched.h>       // Execution scheduling
#include <search.h>      // Search tables
#include <semaphore.h>   // POSIX semaphores
#include <setjmp.h>      // Stack environment declarations
#include <signal.h>      // Signals, see C signal handling
#include <spawn.h>       // Process spawning
#include <stdarg.h>      // Handle Variable Argument List
#include <stdbool.h>     // Boolean type and values, see C data types
#include <stddef.h>      // Standard type definitions, see C data types
#include <stdint.h>      // Integer types, see C data types
#include <stdio.h>       // Standard buffered input/output, see C file input/output
#include <stdlib.h>      // Standard library definitions, see C standard library
#include <string.h>      // Several String Operations, see C string handling
#include <strings.h>     // Case-insensitive string comparisons
//#include <stropts.h>     // Stream manipulation, including ioctl
#include <sys/ipc.h>     // Inter-process communication (IPC)
#include <sys/mman.h>    // Memory management, including POSIX shared memory and memory mapped files
#include <sys/msg.h>     // POSIX message queues
#include <sys/resource.h>// Resource usage, priorities, and limiting
#include <sys/select.h>  // Synchronous I/O multiplexing
#include <sys/sem.h>     // XSI (SysV style) semaphores
#include <sys/shm.h>     // XSI (SysV style) shared memory
#include <sys/socket.h>  // Main Berkeley sockets header
#include <sys/stat.h>    // File information (stat et al.)
#include <sys/statvfs.h> // File System information
#include <sys/time.h>    // Time and date functions and structures
#include <sys/times.h>   // File access and modification times
#include <sys/types.h>   // Various data types used elsewhere
#include <sys/uio.h>     // Vectored I/O operations
#include <sys/un.h>      // Unix domain sockets
#include <sys/utsname.h> // Operating system information, including uname
#include <sys/wait.h>    // Status of terminated child processes (see wait)
#include <syslog.h>      // System error logging
#include <tar.h>         // Magic numbers for the tar archive format
#include <termios.h>     // Allows terminal I/O interfaces
#include <tgmath.h>      // Type-Generic Macros, see C mathematical functions
#include <time.h>        // Type-Generic Macros, see C date and time functions
//#include <trace.h>       // Tracing of runtime behavior (DEPRECATED)
#include <ulimit.h>      // Resource limiting (DEPRECATED in favor of <sys/resource.h>)
#include <unistd.h>      // Various essential POSIX functions and constants
#include <utime.h>       // inode access and modification times
#include <utmpx.h>       // User accounting database functions
#include <wchar.h>       // Wide-Character Handling, see C string handling
#include <wctype.h>      // Wide-Character Classification and Mapping Utilities, see C character classification
#include <wordexp.h>     // Word-expansion like the shell would perform

#define NO_F_OR_D "cd: no such file or directory: "
#define NO_D "cd: not a directory: "
#define STR_NO_PWD "No such file or directory:"
#define MANY_ARGV "cd: too many arguments"

#define FLAG "acEeiLnPsu"

typedef struct builtin_arr { // структура отформатированого масива для билтов
	char **arr;
} bl_arr;

typedef struct environ {
	char **env;
	char **exp;
	char **unset;
} t_env;


#define MX_SHELL_NAME "ush"
#define MX_SHELL_PROMPT "u$h> "
#define MX_COMMAND_DELIM ';'
#define MX_ARGS_DELIM ' '

typedef enum e_literals { // Literal struct
	QUOTE, // `
	SQUOTE, // '
	DQUOTE, // "
	BRACKET, // (
	QBRACKET, // {
	CBRACKET, // )
	CQBRACKET, // }
	SLASH, // "\"
	DOLLAR, // $
}            t_literals;


typedef enum e_builtins { // builtins struct
	MX_ENV,
	MX_CD,
	MX_PWD,
	MX_WHICH,
	MX_ECHO,
	MX_EXPORT,
	MX_UNSET,
	MX_EXIT
}            t_builtins;

typedef enum e_types { // Types stuct
	MX_DIR,
	MX_FILE,
	MX_LINK,
	MX_EFAULT
}            t_types;


typedef struct s_command {
	char *command;
	char **arguments;
	int fl[10];
	int exit;
	struct s_command *next;
}              t_command;


char mx_set_literal(const int literal);
int mx_get_literal(const char c);
int mx_str_arr_size(char **arr);
char **mx_get_commands(const char *stdin_line);
int mx_check_input(char *stdin_line, int *index);
int mx_skip_literal(char *str, int *index, int literal);
t_command *mx_split_to_struct(char *stdin_line);
char **mx_list_to_arr(t_list *list);
t_list *mx_split_commands(char *commands, char delim);
int mx_check_subs_lvls(char *str, int *index);


void mx_builtin_usage(int builtin, char error);
char mx_check_flags(int builtin, int *index, char **args,  bool(*valid)(int *, char *, char *));
bool mx_valid_cd(int *toggle, char *arg, char *flag);
bool mx_valid_pwd(int *toggle, char *arg, char *flag);
// void         mx_ush_loop(t_list *history); // базовый цикл
// char         *mx_ush_read_line(void); // парсинг вводимых данных
// int          mx_launch_process(char **argv); // запуск дочернего процеса
// int          mx_print_pwd(t_command *command); //выводит текущее местополжение
// int          mx_get_array_size(char **arr);
// void         mx_builtin_func(t_command *commands);
// void         mx_change_dir(t_command *command);
// void         mx_chage_dir_and_pwd(char *str); // изменить каталог и pwd
// void         mx_chage_link_dir_pwd(char *str); // перейти по линку и поменять pwd

void mx_ush_loop (t_env *env); // базовый цикл
char *mx_ush_read_line(void); // парсинг вводимых данных
int  mx_launch_process(char **argv); // запуск дочернего процеса
int  mx_get_array_size(char **arr); // получить размер масива
void mx_builtin_func(t_command *commands, t_env *env); //главная ф-я билтинтов


char *mx_create_path(char *command, int d_type, char flag);
char *mx_path_to_canonical(char *str); // нормализация аргумента
int  mx_pwd(t_command *command); //выводит текущее местополжение
void mx_cd(t_command *command); // запуск команды cd


void mx_env(t_command *commands, t_env *env); //запуск команды env
void mx_export(t_command *commands, t_env *env); // обработка export
void mx_unset(t_command *commands, t_env *env); //обработка unset
void mx_env_create(t_env *env); // функция создание среды переменных
int mx_check_flag(char *str, t_command *commands); //проверка приходящих флагов
void mx_dir_file_link(t_command *commands); // проверка и выполнения на папку,линк,файл
void mx_cd_error(t_command *commands, int error_code); //ошибки ф-и cd
void mx_go_dir(t_command *cmd); // переход по папка с флагами и без
void mx_exp_change_dublicate(char *str, t_env *env, int index); // изменить дубликаты в export
void mx_exp_add_argv(t_command *cmd, t_env *env); //добавить данные в export

#endif
