#include "../inc/ush.h"

int main(int argc, char **argv) {
	//Загрузка конфигураций
	argc += 0;
	argv[0] = argv[1];

	//Цыкл команды
	// t_history *history = mx_file_to_struct();
	t_env *env = (t_env*)malloc(sizeof(t_env));
	mx_env_create(env);

	mx_ush_loop(env);

	// system("leaks ush");
	//Очистка памяти
}
