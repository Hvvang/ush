#include "mx_builtins.h"

void mx_error_handle(int builtin, const char *command, int d_type) {
    switch (builtin) {
        case MX_CD:
            if (d_type == MX_ANY)
                fprintf(stderr, "cd: too many arguments\n");
            else if (d_type == MX_LINK) {
                fprintf(stderr, "cd: not a directory: %s\n", command);
            }
            else {
                fprintf(stderr, "cd: ");
                perror(command);
            }
            setenv("status", "1", 1);
    }
    errno = 0;
}
