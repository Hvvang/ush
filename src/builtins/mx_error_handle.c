#include "ush.h"

void mx_error_handle(int builtin, const char *command, int d_type) {
    switch (builtin) {
        case MX_CD:
            if (d_type == MX_ANY)
                fprintf(stderr, "u$h: cd: too many arguments\n");
        	else if (d_type == MX_FILE || d_type == MX_LINK) {
                fprintf(stderr, "u$h: cd: %s: ", command);
                fprintf(stderr, "Not a directory\n");
            }
        	else if (d_type == MX_EFAULT) {
                fprintf(stderr, "u$h: cd: %s: ", command);
                fprintf(stderr, "No such file or directory\n");
            }
    }
}
