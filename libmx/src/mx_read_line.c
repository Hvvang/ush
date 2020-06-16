#include "libmx.h"

static int mx_find_line(char **static_buff, char **buff, char **lineptr, char delim);
static char *mx_cut_static_buff_before_index(char**static_buff, int index);
static int mx_check_static(char **static_buff, char **lineptr, char delim);
static int mx_return_static(char** lineptr, char**static_buff);

int mx_read_line(char **lineptr, int buf_size, char delim, const int fd) {
	static char *static_buff = NULL;
	int i = 0;

	if ((fd <= 0) || (buf_size <= 0) || (read(fd, NULL, 0) == -1))
		return -2;
	if (mx_check_static(&static_buff, lineptr, delim) == 1)
			return mx_strlen(*lineptr);
	char *buff = mx_strnew(buf_size);
	while ((i = read(fd, (void*)buff, buf_size)) > 0) {
		if ((mx_strchr((char*)buff, delim)) == NULL)
			mx_add_buff_to_static(&static_buff, &buff);
		else
			return mx_find_line(&static_buff, &buff, lineptr, delim);
		}
		mx_strdel(&buff);
		if(i == 0 && static_buff != NULL)
			return mx_return_static(lineptr, &static_buff);
		return -1;
}

static int mx_return_static(char** lineptr, char**static_buff) {
	int i = mx_strlen((*lineptr = mx_strdup(*static_buff)));

	mx_strdel(static_buff);
	return i;
}

static int mx_find_line(char **static_buff, char **buff, char **l, char d) {
	char *tmp = NULL;
	int index = 0;

	index = mx_strchr_index(*buff, d);
	if (index > 0) {
		tmp = mx_strnew(index + 1);
		mx_strncpy(tmp, *buff, index);
	}
	*l = mx_strjoin(*static_buff, tmp);
	mx_strdel(static_buff);
	mx_strdel(&tmp);
	tmp = *buff;
	if (tmp != NULL && tmp[index + 1] != '\0') {
		*static_buff = mx_strdup(&tmp[index + 1]);
	}
	mx_strdel(buff);
	if(*l != NULL)
		return mx_strlen(*l);
	*l = mx_strdup("");
	return 0;
}

static char *mx_cut_static_buff_before_index(char **static_buff, int index) {
	char *tmp = NULL;
	char *str = *static_buff;

	if (*static_buff == NULL)
		return NULL;
	if (mx_strlen(*static_buff) == 0) {
		mx_strdel(static_buff);
		return NULL;
	}
	if (str[index + 1] == '\0') {
		mx_strdel(static_buff);
		return NULL;
	}
	tmp = mx_strdup(&str[index + 1]);
	mx_strdel(static_buff);
	return tmp;
}

static int mx_check_static(char **static_buff, char **lineptr, char delim) { 
	int index = mx_strchr_index(*static_buff, delim);

	if (index < 0)
		return 0;
	if (index == 0) {
		*static_buff = mx_cut_static_buff_before_index(static_buff, index);
		*lineptr = mx_strdup("");
		return 1;
	}
	char *tmp = mx_strnew(index);
	*lineptr = mx_strncpy(tmp, *static_buff, index);
	tmp = *static_buff;
	if (tmp[index + 1] != '\0') {
		*static_buff = mx_strdup(&tmp[index + 1]);
		mx_strdel(&tmp);
	}
	else
		mx_strdel(static_buff);
	return 1;
}
