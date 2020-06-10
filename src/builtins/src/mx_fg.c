#include "../inc/mx_builtins.h"

void mx_fg(t_hash_table *hash_table) {
    int status;

    if (hash_table->pids[hash_table->pids_num - 1])
        kill(hash_table->pids[--hash_table->pids_num], SIGCONT);
    if (waitpid(hash_table->pids[hash_table->pids_num], &status, WUNTRACED) != -1) {
        if (!MX_WIFSTOPPED(status)) {
            return;
        }
        else if (MX_WIFSTOPPED(status)) {
            printf("[%d]    %d suspended  %s\n",
                    hash_table->pids_num++,
                    hash_table->pids[hash_table->pids_num],
                    "command");
        }
    }
}
