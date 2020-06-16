#include "libmx.h"

void mx_add_buff_to_static(char **static_buff, char **buff) {
	char *static_tmp = *static_buff;

	*static_buff = mx_strjoin(static_tmp, *buff);
	mx_strdel(&static_tmp);
	mx_memset((void*)(*buff), '\0', mx_strlen(*buff));
}
