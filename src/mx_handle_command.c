#include "ush.h"

void mx_handle_command(char *stdin_line, t_hash_table *hash_table) {
    if (stdin_line[0] != '\0') {
        mx_history_file_appending(stdin_line);
        mx_split_to_struct(stdin_line, hash_table);
    }
}