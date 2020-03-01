#include "ush.h"


static void line_to_arr(char *line) {
	int count = 0;
	for (int i = 0; line[i]; i++)
	printf("%i\n", count);

}

void mx_builtin_func(char *line) {
	// bl_arr *arr = malloc(sizeof(bl_arr)); //структура команды arr

	line_to_arr(line); //  пишем поток в структуру билтин_арр + отформатируем и убираем \n
	printf("%s", line);
}
