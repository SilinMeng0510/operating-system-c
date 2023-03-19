/**
 * Description: Assignment 3: This code read multiple commands through stdin and run them through execvp. The result will be written in created files under name of child pid.
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 03/19/2023
 * Creation date: 03/17/2023
 **/

#include <sys/wait.h> //import library
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND 100 // Max total 100 commands, and each command has max 30 length
#define MAX_LEN 30

int main(void){
	pid_t	pid;	// initialize local variable for managing child processes
	int	status;
	int command;
	char line[MAX_LEN]; //initialize local variable for reading commands
	
	command = 0;
	while(fgets(line, sizeof(line), stdin)) { // reading command line input until there is a break ^D

		++command;	// keep updated with number of command
		if ((pid = fork()) < 0) {	//if fork failed, report error
			fprintf(stderr, "error: can't fork");
		} 
		else if (pid == 0) {	// if fork success
			char filename_out[10];	// create the file name for both out and err
			char filename_err[10];
			sprintf(filename_out, "%d.out", getpid());
        	sprintf(filename_err, "%d.err", getpid());

			int fdout, fderr;	// create file descriptor for both files (out and err)
			if ((fdout = open(filename_out, O_RDWR | O_CREAT | O_APPEND, 0777)) < 0){
				perror("open file failed");	//if open failed, report error
                exit(2);
			}
			if ((fderr = open(filename_err, O_RDWR | O_CREAT | O_APPEND, 0777)) < 0){
				perror("open file failed");	//if open failed, report error
                exit(2);
			}
			
			dup2(fdout, STDOUT_FILENO);	// duplicate the file descriptor of both files into stdout and stderr
			close(fdout);
			dup2(fderr, STDERR_FILENO);
			close(fderr);

			fprintf(stdout, "Starting command %d: child %d pid of parent %d\n", command, getpid(), getppid()); // write first starting message to the out file
			fflush(STDIN_FILENO);	// clean the buffer

			char *args[MAX_LEN];	// parse the command string into an array
			int count = 0;
			args[count] = strtok(line, " ");
			while (args[count] != NULL) {
				count++;
				args[count] = strtok(NULL, " ");
			}

			char *argv[count+1];	// transfer command into a valid array with proper size
			for (int i = 0; i < count; i++){
				argv[i] = args[i];
			}

			int len = strlen(argv[count-1]); // clean newline in our command
			argv[count-1][--len] = '\0';

			argv[count] = NULL;	// set the last element in command to NULL for execvp

			if (execvp(argv[0], argv) < 0){	// execvp our command, replacing the current process
				perror("execvp failed");	//if execvp failed, report error
				exit(2);
			}
		}
	}

	while((pid = wait(&status)) > 0){	// wait until all child processes are done
		char filename_out[10];	// create the file name for both out and err
		char filename_err[10];
		sprintf(filename_out, "%d.out", pid);
        sprintf(filename_err, "%d.err", pid);

		int fdout, fderr;	// get file descriptor for both files (out and err)
		if ((fdout = open(filename_out, O_RDWR | O_CREAT | O_APPEND, 0777)) < 0){
			perror("open file failed");	//if open failed, report error
            exit(2);
		}
		if ((fderr = open(filename_err, O_RDWR | O_CREAT | O_APPEND, 0777)) < 0){
			perror("open file failed");	//if open failed, report error
            exit(2);
		}

		dup2(fdout, STDOUT_FILENO);	// duplicate the file descriptor of both files into stdout and stderr
		close(fdout);
		dup2(fderr, STDERR_FILENO);
		close(fderr);

		fprintf(stdout, "Finished child %d pid of parent %d\n", pid, getpid());	// write end message to the out file
		fflush(STDIN_FILENO);	// clean the buffer

		if(WIFEXITED(status)){	// check if the command exit successfully with 0
            fprintf(stderr, "Exited with exitcode = %d\n", WEXITSTATUS(status));
        }
		else if(WTERMSIG(status)){	// check if the command exit abnormally in signal kill
            fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
        }
		else if(WIFSIGNALED(status)){	// check if the command exit abnormally
            fprintf(stderr, "Exited with exitcode = %d\n", WTERMSIG(status));
        }
	}

	exit(0);
}
