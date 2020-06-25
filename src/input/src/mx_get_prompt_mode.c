#include "mx_input.h"

char **mx_get_prompt_mode(void) {
    static char *prompt = NULL;

    return &prompt;
}
