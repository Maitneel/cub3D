#include <sys/fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void child(const pid_t pairent_pid) {
	for (size_t i = 0; i < 1000 * 100; i++) {
		kill(pairent_pid, SIGUSR1);
	}
}

void handle_func(int sigid) {
	char hoge[10];
	read(123, hoge, 1);
}

int main() {
	const pid_t pairent_pid = getpid();
	pid_t pid = fork();
	
	if (pid == 0) {
		child(pairent_pid);
		exit(0);
	}

	signal(SIGUSR1, handle_func);
	const int line_size = 1024;
	char line[line_size];
	int fd = open("Makefile", O_RDONLY);
	while (0 < read(fd, line, line_size - 1)) {
		write(STDOUT_FILENO, line, line_size -1);
		bzero(line, line_size);
		kill(pairent_pid, SIGUSR1);
	}
	write(STDOUT_FILENO, "\n", 1);
	printf("waiting\n");
	wait(NULL);
	read(fd, line, 1);
	perror("read");
	if (read(fd, line, 0) != 0 || close(fd) != 0) {
		perror(NULL);
	}
}