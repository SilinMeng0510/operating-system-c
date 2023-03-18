#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LEN 30

int main(void){
	pid_t	pid;
	int		status;
	int fd1, fd2;
	char line[MAX_LEN];
	
	while(fgets(line, sizeof(line), stdin)) {

		if ((pid = fork()) < 0) {
			fprintf(stderr, "error: can't fork");
		} 
		else if (pid == 0) {
			char *filename_out;
			snprintf(filename_out, 10, "%d.out", getpid());
			printf("%s", filename_out);
			fd1 = open(filename_out, O_RDWR | O_CREAT | O_APPEND, 0777);
			dup2(fd1, 1);

			printf("%s", filename_out);

			// char *filename_err;
			// snprintf(filename_err, 10, "%d.err", getpid());
			// int file_desc_err = open(filename_err, O_RDWR | O_CREAT | O_APPEND, 0777);
			// dup2(file_desc_err, 2);

			// char *args[30];
			// int count = 0;
			// args[count] = strtok(line, " ");
			// while (args[count] != NULL) {
			// 	count++;
			// 	args[count] = strtok(NULL, " ");
			// }
			// char *argv[count+1];
			// for (int i = 0; i < count; i++){
			// 	argv[i] = args[i];
			// }

			// int len = strlen(argv[count-1]);
			// argv[count-1][--len] = '\0';

			// argv[count] = NULL;
			// execvp(argv[0], argv);
			// perror("execvp failed");
			// close(file_desc_err);
			exit(1);
		}

		if ((pid = waitpid(pid, &status, 0)) < 0){
			printf("DONE ");
		}
	}

	exit(0);
}
