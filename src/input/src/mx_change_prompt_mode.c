#include "mx_input.h"

static void clear_prompt(int prompt_size, char *input, int pos) {
    int len = strlen(input);
    char *temp = mx_strnew(len + prompt_size);

    while (pos > 0) {
        printf("\b");
        pos = pos - 1;
    }
    memset(temp, ' ', len + prompt_size);
    printf("%s", temp);
    memset(temp, '\b', len + prompt_size);
    printf("%s", temp);
    mx_strdel(&temp);
}

void mx_change_prompt_mode(char *line, int pos) {
    char **prompt = mx_get_prompt_mode();
    int size = strlen(*prompt);
    int i = pos + size;

    if (!strcmp(*prompt, MX_SHELL_PROMPT)) {
        free(*prompt);
        *prompt = mx_zsh_prompt();
    }
    else {
        free(*prompt);
        *prompt = strdup(MX_SHELL_PROMPT);
    }
    clear_prompt(size, line, i);
    printf("%s", *prompt);
    fflush(stdout);
    printf("%s", line);
    while (pos < (int)strlen(line)) {
        printf("\b");
        pos++;
    }
}
