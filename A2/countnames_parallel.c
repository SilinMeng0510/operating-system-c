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

typedef struct my_data {
    char name[MAX_LEN];
    int count;
} my_data;

int count(FILE *file, struct my_data *namecounts){

    char line[MAX_LEN]; 
    int namesMap = 0;
    int lineCounter = 1;

    while (fgets(line, sizeof(line), file)) { // This loop will keep retreving names from each lines of the file until reaching the end
        if (line[0] == '\n' || line[0] == ' ') { // Printing Error message while there is a empty line
            fprintf(stderr, "Warning - Line %d is empty.\n", lineCounter);
            ++lineCounter; // Count which line we are in
            continue;
        }
        int found = 0;
        for (int i = 0; i < namesMap; i++) { // This for loop will check if the name is already been found
            char temp_line[MAX_LEN];
            strncpy(temp_line, line, strlen(line) - 1);
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

    return namesMap;
}


int main(int argc, char* argv[])
{
    if (argv[1] == NULL){ // exit if there is no file specified
        exit(0);
    }

    int pid;
    struct my_data total_namecounts[MAX_NAME] = { { '\0', 0 } };
    int total_count = 0;
    int pfds[argc - 1][2];
    
    for(int i = 1; i < argc; ++i){
        pipe(pfds[i-1]);
        pid = fork();
        if (pid < 0){
            fprintf(stderr, "error: can't fork");
        }
        else if (pid == 0) {
            FILE *file = fopen(argv[i], "r"); // set up file opener and variables that will be used later
            struct my_data namecounts[MAX_NAME] = { { '\0', 0 } };
            int namesMap = 0;
            if (file == NULL) { // return error if file can't be opened
                fprintf(stderr, "error: cannot open file %s\n", argv[i]);
                write(pfds[i-1][1], &namesMap, sizeof(namesMap));
                write(pfds[i-1][1], namecounts, sizeof(my_data) * MAX_NAME);
                exit(1);
            }
            namesMap = count(file, namecounts);
            fclose(file);
            write(pfds[i-1][1], &namesMap, sizeof(namesMap));
            write(pfds[i-1][1], namecounts, sizeof(my_data) * MAX_NAME);
            return 0;
        }
        int pfds[2];
        pipe(pfds);
    }

    int pip_count = 0;
    while(wait(NULL) != -1){
        struct my_data namecounts[MAX_NAME] = { { '\0', 0 } };
        int namesMap = 0;
        read(pfds[pip_count][0], &namesMap, sizeof(namesMap));
        read(pfds[pip_count][0], namecounts, sizeof(my_data) * MAX_NAME);

        for (int i = 0; i < namesMap; i++) {
            int found = 0;
            for (int j = 0; j < total_count; j++){
                if (strcmp(total_namecounts[j].name, namecounts[i].name) == 0){
                    total_namecounts[j].count += namecounts[i].count;
                    found = 1;
                    break;
                }
            }
            if (!found){
                strcpy(total_namecounts[total_count].name, namecounts[i].name);
                total_namecounts[total_count].count = namecounts[i].count;
                total_count++;
            }
        }
        pip_count++;
    }

    for (int i = 0; i < total_count; i++) { // This for loop will print all the names and its occurence.
        fprintf(stdout, "%s: %d\n", total_namecounts[i].name, total_namecounts[i].count);
    }

    return 0;
}