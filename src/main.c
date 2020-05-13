#include "../inc/ush.h"

t_hash_table *create_hash_table(void) {
	t_hash_table *hash_table = (t_hash_table*)malloc(sizeof(t_hash_table));

	hash_table->export = (t_export*)malloc(sizeof(t_export));
	hash_table->export_size = 0;
	return hash_table;
}


int main(int argc, char **argv) {
	//Загрузка конфигураций
	argc += 0;
	argv[0] = argv[1];

	//Цыкл команды
	t_hash_table *hash_table = create_hash_table();

	mx_create_export(hash_table);
	mx_ush_loop(hash_table);

	// system("leaks ush");
	//Очистка памяти
}
