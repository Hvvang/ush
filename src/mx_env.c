#include "ush.h"

void mx_env(t_command *commands) {

	for (int i = 0; commands->env[i]; i++) {
		printf("%s\n", commands->env[i]);
	}
	mx_ush_loop();
}

