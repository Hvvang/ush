#include "ush.h"

int mx_get_array_size(char **arr) {
	int count = 0;
	for (int i = 0; arr[i]; i++)
		count++;
	return count;
}
