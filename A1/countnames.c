/**
 * Description: Assignment 1: countnames: This code takes a file of names and output the names and their occurrence using an array
 * Author names:Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/18/23
 * Creation date: 2/10/23
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

int main(int argc, char* argv[])
{
    if (argv[1] == NULL){ // exit if there is no file specified
        exit(0);
    }
    FILE *file = fopen(argv[1], "r"); // set up file opener and variables that will be used later
    if (file == NULL) { // return error if file can't be opened
    printf("error: cannot open file\n");
    exit(1);
    }
    char line[256];
    char names[100][30];
    int occurence[100] = {0};
    int namesMap = 0;
    int lineCounter = 1;

    while (fgets(line, sizeof(line), file)) { // This loop will keep retreving names from each lines of the file until reaching the end
        if (line[0] == '\n') { // Printing Error message while there is a empty line
            fprintf(stderr, "Warning - Line %d is empty.\n", lineCounter);
            ++lineCounter; // Count which line we are in
            continue;
        }
        int found = 0;
        for (int i = 0; i < namesMap; i++) { // This for loop will check if the name is already been found
            if (strcmp(names[i], line) == 0) { // If yes, add occurence into the name
                occurence[i]++;
                found = 1;
                break;
            }
        }
        if (!found) { // If the name is not found previously, we will add the name into the array, and set occurence to 1
            strcpy(names[namesMap], line);
            occurence[namesMap] = 1;
            namesMap++;
        }
        ++lineCounter; // Count which line we are in
    }
    fclose(file);
    
    int len;
    for (int i = 0; i < namesMap; i++) { // This for loop will print all the names and its occurence.
        len = strlen(names[i]);
        names[i][--len] = '\0'; // This line will set newline \n into \0, so newline will not be printed out
        fprintf(stdout, "%s: %d\n", names[i], occurence[i]);
    }

    return 0;
}
