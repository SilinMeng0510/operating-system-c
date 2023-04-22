/**
 * Description: Assignment 3: This code read multiple commands through stdin and run them through execvp. The result will be written in created files under name of child pid.
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 03/19/2023
 * Creation date: 03/17/2023
 **/

#include <sys/wait.h> //import library
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

/** You might need to duplicate the command string to ensure you don't overwrite the previous command each time a new line is read from the input file. 
Or you might not need to duplicate it. It depends on your implementation. **/
char *comdup(char *s) /* make a duplicate of s */
{
    char *p;
    p = (char *) malloc(strlen(s)+1); /* +1 for ’\0’ */
    if (p != NULL)
       strcpy(p, s);
    return p;
}

struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    struct timespec starttime;   // the time when process started
    struct timespec finishtime;	// the time when process end
    int index;          // this is the line index in the input text file 
    int pid;            // the process id. you can use the pid result of wait to lookup in the hashtable 
    char *command;      // command. This is good to store for when you decide to restart a command
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* This is the hash function: form hash value for pid number */
unsigned hash(int pid)
{
    unsigned hashval = pid;
    return hashval % HASHSIZE;
}

/* lookup: look for pid in hashtab */
/* This is traversing the linked list under a slot of the hash table. The array position to look in is returned by the hash function */
struct nlist *lookup(int pid)
{
    struct nlist *np;
    for (np = hashtab[hash(pid)]; np != NULL; np = np->next)
        if (pid == np->pid)
            return np; 
    return NULL; 
}

/* insert: put (command, pid, index) in hashtab */
/* This insert returns a nlist node. Thus when you call insert in your main function  */
/* you will save the returned nlist node in a variable (mynode). */
struct nlist *insert(char *command, int pid, int index)
{
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(pid)) == NULL) { 
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->command = comdup(command)) == NULL)
            return NULL;
		np->index = index;
        np->pid = pid;
        hashval = hash(pid);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    return np;
}

void executeCommand(char* line, int index, int restart);

// -----------------------------------------
// function add_size will add an extra string space to an array.
// This function is adding more memory space for our array, using realloc
// Returns the pointer of the reallocated array of string (updated)
char** add_size(char** array, int size) {

    array = (char**) realloc(array, sizeof(char*) * size);	// reallocate the space for bigger array

    return array;
}// end add_size


// -----------------------------------------
// function new_size will create an initial array stroing 10 pointers.
// This function is allocating 10 char* memory space for our array, using malloc
// Returns the pointer of new array of string 
char** new_arr(char** array, int size) {

    array = (char**) malloc(sizeof(char*) * size);	// allocate an array that can store specified number of strings

    return array;
}// end new_arr


// -----------------------------------------
// function alloc_string will allocate memory space for a string.
// This function is allocating memory space of the input length for our array, using malloc
// Returns the pointer of string 
void alloc_string(char** array, int index, int length) {

    array[index] = (char*) malloc(sizeof(char) * length); // allocate space for the string

	return;
}// end alloc_string

int main(void){
	pid_t	pid;	// initialize local variable for managing child processes
	int	status;
	int index;

	char *line = NULL;	// initailize the input line and buffer len
	size_t len = 0;

	char **array = NULL;	// initialize the array

	index = 0;	// initialize the input index and total size with 10 strings
	int SIZE = 1; // initiate the size of array to 1 strings

	array = new_arr(array, SIZE);  // initiate 1 string
	while(getline(&line, &len, stdin) != -1) {
        // check if there is more string needed
        if (index == SIZE) {
            SIZE += 1;
            array = add_size(array, SIZE);
        }

		// insert command read from stdin into char** array
		alloc_string(array, index, len);
        strcpy(array[index], line);

		++index;
	}
	free(line);

	struct nlist *np; // initialize the pointer to hash list

	char filename_out[10];	// create the file name for both out and err
	char filename_err[10];

	struct timespec start, finish; // initialize time spec

	for(int cml = 0; cml < index; cml++) { // implement process in parallel

		clock_gettime(CLOCK_MONOTONIC, &start);
		if ((pid = fork()) < 0) {	//if fork failed, report error
			fprintf(stderr, "error: can't fork (parent error)");
		} 
		else if (pid == 0) {	// if fork success
			executeCommand(array[cml], cml + 1, 0);
		}
		else if (pid > 0) {
			if ((np = insert(array[cml], pid, cml + 1)) == NULL){
				perror("insert list failed (parent error)");	//if insert failed, report error
                exit(2);
			}
			np->starttime = start;
		}
	}

	//now deallocate it
	for(int i = 0; i < SIZE; i++){
		free(array[i]);
	}
	free(array);

	while((pid = wait(&status)) > 0){	// wait until all child processes are done
		clock_gettime(CLOCK_MONOTONIC, &finish);
		if ((np = lookup(pid)) == NULL){
			perror("lookup list failed (parent error)");	//if lookup failed, report error
            exit(2);
		}
		np->finishtime = finish;

		sprintf(filename_out, "%d.out", pid);
        sprintf(filename_err, "%d.err", pid);

		int fdout, fderr;	// get file descriptor for both files (out and err)
		if ((fdout = open(filename_out, O_RDWR | O_CREAT | O_APPEND, 0777)) < 0){
			perror("open file failed (parent error)");	//if open failed, report error
            exit(2);
		}
		if ((fderr = open(filename_err, O_RDWR | O_CREAT | O_APPEND, 0777)) < 0){
			perror("open file failed (parent error)");	//if open failed, report error
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

		int elapsed = (np->finishtime.tv_sec - np->starttime.tv_sec);
		fprintf(stdout, "Finished at %ld, runtime duration %d\n", np->finishtime.tv_sec, elapsed);	// write runtime message to the out file
		fflush(STDIN_FILENO);	// clean the buffer
		if (elapsed <= 2){
			fprintf(stderr, "spawning too fast\n");	// write "too fast" message to the err file
		}
		else {
			clock_gettime(CLOCK_MONOTONIC, &start);
			if ((pid = fork()) < 0) {	//if fork failed, report error
				fprintf(stderr, "error: can't fork (parent error)");
			} 
			else if (pid == 0) {	// if fork success
				executeCommand(np->command, np->index, 1);
			}
			else if (pid > 0) {
				if ((np = insert(np->command, pid, np->index)) == NULL){
					perror("insert list failed");	//if insert failed, report error
                	exit(2);
				}
				np->starttime = start;
			}
		}
	}

	// Free all nodes in hashtable
    for(int j = 0; j < HASHSIZE; j++) {
        struct nlist *temp = hashtab[j];
        while(temp != NULL) {
            struct nlist* next = temp->next;
			free(temp->command);
            free(temp);
            temp = next;
        }
        hashtab[j] = NULL;
    }

	exit(0);
}

void executeCommand(char* line, int index, int restart){
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

	if(restart){
		fprintf(stdout, "RESTARTING\n"); // write first starting message to the out file
		fflush(STDIN_FILENO);	// clean the buffer
		fprintf(stderr, "RESTARTING\n");	// write "too fast" message to the err file
	}
	fprintf(stdout, "Starting command %d: child %d pid of parent %d\n", index, getpid(), getppid()); // write first starting message to the out file
	fflush(STDIN_FILENO);	// clean the buffer

	char *args[strlen(line) + 1];	// parse the command string into an array
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
