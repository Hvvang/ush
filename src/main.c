#include "ush.h"

int main(int argc, char **argv) {
	//Загрузка конфигураций
	argc += 0;
	argv[0] = argv[1];
	t_list *history = NULL;
	//Цыкл команды
	mx_ush_loop(history);

	// system("leaks ush");
	//Очистка памяти
}
