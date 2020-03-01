#include "libmx.h"

bool mx_isspace(char c) {
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return 1;
	else
		return 0;
}
