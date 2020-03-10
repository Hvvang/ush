#include "ush.h"

int main(int argc, char **argv, char **envp) {
	//Загрузка конфигураций
	argc += 0;
	argv[0] = argv[1];
	//Цыкл команды
	for (int i = 0; envp[i]; i++)
		printf("%s\n", envp[i]);
	t_env *env = (t_env*)malloc(sizeof(t_env));
	mx_env_create(env);

	mx_ush_loop(env);

	// system("leaks ush");
	//Очистка памяти
}
