#include "mx_shell.h"

#define MX_KEY_NOT_FOUND -1
#define MX_VAR_EXISTED 0
#define MX_NEW_VAR 1

int mx_find_key_index(char *command, t_hash_table *hash_table, int equal) {
    char *command_key = (equal > 0) ?
                        mx_strndup(command, equal) :
                        mx_strdup(command);

    for (unsigned i = 0; i < hash_table->export_size; i++) {
        if (!strcmp(hash_table->export[i].key, command_key)) {
            mx_strdel(&command_key);
            return i;
        }
    }
    mx_strdel(&command_key);
    return MX_KEY_NOT_FOUND;
}

static int change_var_value(char *command, t_hash_table *hash_table,
                               int equal) {
    int index = mx_find_key_index(command, hash_table, equal);

    if (index != MX_KEY_NOT_FOUND) {
        if (equal > 0) {
            free(hash_table->export[index].value);
            hash_table->export[index].value = mx_strdup(command + equal + 1);
            setenv(hash_table->export[index].key,
                hash_table->export[index].value,
                1);
        }
        return MX_VAR_EXISTED;
    }
    return MX_KEY_NOT_FOUND;
}

int mx_push_to_export(char *command, t_hash_table *hash_table) {
    int equal = mx_get_char_index(command, '=');
    int new_size = (hash_table->export_size + 1) * sizeof(t_var_map);
    int index = hash_table->export_size;

    if (change_var_value(command, hash_table, equal) == MX_VAR_EXISTED)
        return MX_VAR_EXISTED;
    hash_table->export = realloc(hash_table->export, new_size);
    if (equal > 0) {
        hash_table->export[index].key = mx_strndup(command, equal);
        hash_table->export[index].value = mx_strdup(command + equal + 1);
        setenv(hash_table->export[index].key,
               hash_table->export[index].value,
               1);
    }
    else {
        hash_table->export[index].key = mx_strdup(command);
        hash_table->export[index].value = NULL;
    }
    hash_table->export_size++;
    return MX_NEW_VAR;
}
