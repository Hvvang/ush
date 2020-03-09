#include "ush.h"

int check_flag(char *str, t_command *commands) {

	for (int i = 1; str[i]; i++) {
		for (int j = 0; FLAG[j]; j++) {
			if (str[i] == FLAG[j])
				commands->fl[j] = 1;
		}
	}
	return 0;
}