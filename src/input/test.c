#include "inc/mx_input.h"
#include "../parser/inc/mx_parser.h"
#include "../builtins/inc/mx_builtins.h"

void pop_front(t_command **head) {
	t_command *prev = NULL;

	if (!head || !(*head))
		return ;
    else {
        mx_strdel(&((*head)->command));
        mx_del_str_arr(((*head)->arguments));
        if ((*head)->next == NULL) {
			// printf ("1\n");
            free(*head);
            *head = NULL;
            return ;
        }
		// printf ("2\n");
        prev = (*head)->next;
        free(*head);
        *head = prev;
    }
}

int main() {
    int i = 2;
    t_env *env = (t_env *)malloc(sizeof(t_env));

    mx_env_create(env);
    while (i--) {
        char *line = mx_ush_read_line();
        t_command *commands = mx_split_to_struct(line);

        mx_pwd(commands);
        //mx_cd(commands);
        pop_front(&commands);
        mx_strdel(&line);
    }
    if (env->export)
        mx_del_str_arr(env->export);
    free(env);
    return 0;
}
