#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LEN 30

int main(void){
	pid_t	pid;
	int	status;
	int command;
	char line[MAX_LEN];
	
	command = 0;
	while(fgets(line, sizeof(line), stdin)) {

		++command;
		if ((pid = fork()) < 0) {
			fprintf(stderr, "error: can't fork");
		} 
		else if (pid == 0) {
			char filename_out[10];
			char filename_err[10];
			sprintf(filename_out, "%d.out", getpid());
        	sprintf(filename_err, "%d.err", getpid());

			int fdout, fderr;
			if ((fdout = open(filename_out, O_RDWR | O_CREAT | O_APPEND, 0777)) < 0){
				perror("open file failed");
                exit(2);
			}
			if ((fderr = open(filename_err, O_RDWR | O_CREAT | O_APPEND, 0777)) < 0){
				perror("open file failed");
                exit(2);
			}
			
			dup2(fdout, STDOUT_FILENO);
			close(fdout);
			dup2(fderr, STDERR_FILENO);
			close(fderr);

			fprintf(stdout, "Starting command %d: child %d pid of parent %d\n", command, getpid(), getppid());
			fflush(STDIN_FILENO);

			char *args[30];
			int count = 0;
			args[count] = strtok(line, " ");
			while (args[count] != NULL) {
				count++;
				args[count] = strtok(NULL, " ");
			}

			char *argv[count+1];
			for (int i = 0; i < count; i++){
				argv[i] = args[i];
			}

			int len = strlen(argv[count-1]);
			argv[count-1][--len] = '\0';

			argv[count] = NULL;

			if (execvp(argv[0], argv) < 0){
				perror("execvp failed");
				exit(2);
			}
		}
	}

	while((pid = wait(&status)) > 0){
		char filename_out[10];
		char filename_err[10];
		sprintf(filename_out, "%d.out", pid);
        sprintf(filename_err, "%d.err", pid);

		int fdout, fderr;
		if ((fdout = open(filename_out, O_RDWR | O_CREAT | O_APPEND, 0777)) < 0){
			perror("open file failed");
            exit(2);
		}
		if ((fderr = open(filename_err, O_RDWR | O_CREAT | O_APPEND, 0777)) < 0){
			perror("open file failed");
            exit(2);
		}

		dup2(fdout, STDOUT_FILENO);
		close(fdout);
		dup2(fderr, STDERR_FILENO);
		close(fderr);

		fprintf(stdout, "Finished child %d pid of parent %d\n", pid, getpid());
		fflush(STDIN_FILENO);

		if(WIFEXITED(status)){
            fprintf(stderr, "Exited with exitcode = %d\n", WEXITSTATUS(status));
        }
		else if(WTERMSIG(status)){
            fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
        }
		else if(WIFSIGNALED(status)){
            fprintf(stderr, "Exited with exitcode = %d\n", WTERMSIG(status));
        }
	}

	exit(0);
}
