/**
 * Description: Assignment 2: countnames_parallel: This code takes multiple file of names and output the names and their occurrence using an array
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 3/3/23
 * Creation date: 2/25/23
 **/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_LEN 30

typedef struct my_data {    // a structured data with 30 characters name and occurance count, named my_data
    char name[MAX_LEN];
    int count;
} my_data;

/**
* This function counts and stores the occurence of each name in a file provided in the 
*     parameter and stores them in the namecounts struct then it returns the number of unique names in the file
* Assumption: names from file are separated by a newline character
* Input parameters: file(FILE), namescounts(struct), file_name(char)
* Returns: an integer
**/
int count(FILE *file, struct my_data *namecounts, char *file_name){

    char line[MAX_LEN]; //necessary local variable for reading file
    int namesMap = 0;
    int lineCounter = 1;

    while (fgets(line, sizeof(line), file)) { // This loop will keep retreving names from each lines of the file until reaching the end
        if (line[0] == '\n' || line[0] == ' ') { // Printing Error message while there is a empty line
            fprintf(stderr, "Warning - file %s line %d is empty.\n", file_name, lineCounter);
            ++lineCounter; // Count which line we are in
            continue;
        }
        int found = 0;
        for (int i = 0; i < namesMap; i++) { // This for loop will check if the name is already been found
            char temp_line[MAX_LEN];
            strncpy(temp_line, line, strlen(line) - 1);  // check two version of input, with /n and without /n
            if (strcmp(namecounts[i].name, line) == 0 || strcmp(namecounts[i].name, temp_line) == 0) { // If yes, add occurence into the name
                namecounts[i].count++;
                found = 1;
                break;
            }
        }
        if (!found) { // If the name is not found previously, we will add the name into the array, and set occurence to 1
            if (line[strlen(line) - 1] == '\n'){
                strncpy(namecounts[namesMap].name, line, strlen(line) - 1);
            }
            else {
                strcpy(namecounts[namesMap].name, line);
            }
            namecounts[namesMap].count = 1;
            namesMap++;
        }
        ++lineCounter; // Count which line we are in
    }

    return namesMap;    // return how many name is recorded
}


int main(int argc, char* argv[])
{
    if (argv[1] == NULL){ // exit if there is no file specified
        exit(0);
    }

    int pid;    // initial local variables, such as pid for fork()
    struct my_data total_namecounts[MAX_NAME] = { { '\0', 0 } }; // my_data for result
    int total_count = 0; // total_count for size of result
    int pfds[argc - 1][2]; // pfds array for pipe between parent and different childs

    for(int i = 1; i < argc; ++i){
        pipe(pfds[i-1]);    // pipe with one child each loop
        pid = fork();   // fork new child process
        if (pid < 0){   // if fork is not successful, return error
            fprintf(stderr, "error: can't fork");
        }
        else if (pid == 0) {
            FILE *file = fopen(argv[i], "r"); // set up file opener and variables that will be used later
            struct my_data namecounts[MAX_NAME] = { { '\0', 0 } };
            int namesMap = 0;
            if (file == NULL) { // return error if file can't be opened
                fprintf(stderr, "range: cannot open file %s\n", argv[i]);
                write(pfds[i-1][1], &namesMap, sizeof(namesMap));   // write nothing to parent for breaking loop
                write(pfds[i-1][1], namecounts, sizeof(my_data) * MAX_NAME);
                exit(1);
            }
            namesMap = count(file, namecounts, argv[i]); // implement function that return namecounts result of a file and number of result
            fclose(file);   // close file
            write(pfds[i-1][1], &namesMap, sizeof(namesMap)); // write results to parent through pipe
            write(pfds[i-1][1], namecounts, sizeof(my_data) * MAX_NAME);
            return 0;
        }
    }

    int pip_count = 0;  // count the pip corresponding to each child process
    while(wait(NULL) != -1){
        struct my_data namecounts[MAX_NAME] = { { '\0', 0 } }; // initialize new variable to store result from child
        int namesMap = 0;
        read(pfds[pip_count][0], &namesMap, sizeof(namesMap));  // read result from child processes
        read(pfds[pip_count][0], namecounts, sizeof(my_data) * MAX_NAME);

        for (int i = 0; i < namesMap; i++) {    // this for loop with combine result from child into the main result from parent
            int found = 0;
            for (int j = 0; j < total_count; j++){  // this for loop will find if the name is already exist in main result of parent
                if (strcmp(total_namecounts[j].name, namecounts[i].name) == 0){ // if found, combine the count
                    total_namecounts[j].count += namecounts[i].count;
                    found = 1;
                    break;
                }
            }
            if (!found){    // if not found, we will add it into the main result of parent
                strcpy(total_namecounts[total_count].name, namecounts[i].name);
                total_namecounts[total_count].count = namecounts[i].count;
                total_count++;
            }
        }
        pip_count++;    // increment pip count for next child
    }

    for (int i = 0; i < total_count; i++) { // This for loop will print all the names and its occurence.
        fprintf(stdout, "%s: %d\n", total_namecounts[i].name, total_namecounts[i].count);
    }

    return 0;
}