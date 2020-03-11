#include "ush.h"

int main(int argc, char **argv) {
	//Загрузка конфигураций
	argc += 0;
	argv[0] = argv[1];
	//Цыкл команды

	t_env *env = (t_env*)malloc(sizeof(t_env));
	mx_env_create(env);

	mx_ush_loop(env);

	// system("leaks ush");
	//Очистка памяти
}
