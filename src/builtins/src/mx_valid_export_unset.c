#include "../inc/mx_builtins.h"

bool mx_valid_export_unset(t_command *cmd) {
	if (!cmd->arguments[0])
		return true;
	if (!strcmp(cmd->arguments[0], "--") && !cmd->arguments[1])
		return true;
	return false;
}
