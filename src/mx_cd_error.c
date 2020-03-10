#include "ush.h"

void mx_cd_error(t_command *commands, int error_code) {
	if (error_code == 2) {
		fprintf(stderr, "%s", "u$h: cd: ");
		if (commands->fl[5] || commands->fl[7])
			fprintf(stderr, "%s", commands->arguments[1]);
		else
			fprintf(stderr, "%s", commands->arguments[0]);
		fprintf(stderr, "%s\n", ": Not a directory");
	}
	if (error_code == 1) {
		fprintf(stderr, "%s", "u$h: cd: ");
		if (commands->fl[5] || commands->fl[7])
			fprintf(stderr, "%s", commands->arguments[1]);
		else
			fprintf(stderr, "%s", commands->arguments[0]);
		fprintf(stderr, "%s\n", ": No such file or directory");
	}
	return ;
}
