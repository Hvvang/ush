#include "ush.h"

char *mx_curl_normal(char *str) { //нормализация пути
	char *buff = (char*)malloc(sizeof(char) * strlen(str));

	if (str[0] == '/' && str[1] != '.')
			return strcpy(buff, str);
	if (str[0] == '.' && str[1] == '.')
			return strcpy(buff, str);
	for (int i = 0, j = 0; str[i]; i++) {
		if (str[i] == '.' || str[i] == '/')
			i++;
		else {
			buff[j] = str[i];
			buff[j + 1] = '\0';
			j++;
		}
	}
	return buff;
}
