#include "ush.h"

int mx_check_flag(char *str, t_command *commands) {
	if (str[0] == '-') {
		for (int i = 1; str[i]; i++) {
			if (str[i] == 'a')
				commands->fl[0] = 1;
			if (str[i] == 'c')
				commands->fl[1] = 1;
			if (str[i] == 'E')
				commands->fl[2] = 1;
			if (str[i] == 'e')
				commands->fl[3] = 1;
			if (str[i] == 'i')
				commands->fl[4] = 1;
			if (str[i] == 'L') { // если последний флаг L, флаг P выкл
				if (commands->fl[7] == 1) {
					commands->fl[7] = 0;
					commands->fl[5] = 1;
				}
				else
					commands->fl[5] = 1;
			}
			if (str[i] == 'n')
				commands->fl[6] = 1;
			if (str[i] == 'P') { // если последний флаг P, флаг L выкл
				if (commands->fl[5] == 1) {
					commands->fl[5] = 0;
					commands->fl[7] = 1;
				}
				else
					commands->fl[7] = 1;
			}
			if (str[i] == 's')
				commands->fl[8] = 1;
			if (str[i] == 'u')
				commands->fl[9] = 1;
		}
	}
	return 0;
}
