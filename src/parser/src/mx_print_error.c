#include "../inc/mx_parser.h"

int mx_print_error(int error) {
    setenv("status", mx_itoa(error), 1);
    switch (error) {
        case -1:
            fprintf(stderr,
                    "%s: syntax error: missing terminating character\n",
                    MX_SHELL_NAME);
            break;
        case -2:
            fprintf(stderr,
                    "%s: syntax error: missing terminating character\n",
                    MX_SHELL_NAME);
            break;
        case -3:
            fprintf(stderr,
                    "%s: syntax error: missing subsitution character\n",
                    MX_SHELL_NAME);
            break;
        case -4:
            fprintf(stderr,
                    "%s: syntax error: missing brace character\n",
                    MX_SHELL_NAME);
            break;
        // case 4:
        //     fprintf(stderr,
        //             "%s: command contain forbidden character\n",
        //             MX_SHELL_NAME);
    }
    return 0;
}
