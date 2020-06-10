#include "../inc/ush.h"

t_hash_table *create_hash_table(void) {
	t_hash_table *hash_table = (t_hash_table*)malloc(sizeof(t_hash_table));

	hash_table->pids_num = 0;
	hash_table->pids = (pid_t *)malloc(sizeof(pid_t) * 1000);
	hash_table->export = (t_var_map*)malloc(sizeof(t_var_map));
	hash_table->export_size = 0;
	return hash_table;
}

void sigint_handler(int signo) {
	printf("Caught SIGINT = %d\n", signo);
}

void sigquit_handler(int signo) {
    printf("Caught SIGQUIT = %d\n", signo);
}

void sigstp_handler(int signo) {
	printf("p_pid = %d, pid = %d\n", getppid(), getpid());
    printf("Caught SIGTSTP = %d\n", signo);
	sleep(2);
	// kill(getpid(), SIGCONT);
}

void sigcont_handler(int signo) {
    printf("Caught SIGCONT = %d\n", signo);
}

int main(int argc, char **argv) {
	argc += 0;
	argv[0] = argv[1];

	t_hash_table *hash_table = create_hash_table();
	signal(SIGINT, sigint_handler);
	signal(SIGCONT, sigcont_handler);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGTSTP, sigstp_handler);
	mx_create_vars(hash_table);
	mx_ush_loop(hash_table);

	// system("leaks ush");
}
