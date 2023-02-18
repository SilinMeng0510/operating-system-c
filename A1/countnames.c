/**
 * Description: Assignment 1: Names occurence to file: This code takes a file of names and output the names and their occurence to a new file
 * Author names:Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/16/23
 * Creation date: 2/10/23
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

int main(int argc, char* argv[])
{
    FILE *file = fopen(argv[1], "r");
    char line[256];
    char names[100][30];
    int occurence[100] = {0};
    int namesMap = 0;
    int lineCounter = 1;

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '\n') {
            fprintf(stderr, "Warning - Line %d is empty.\n", lineCounter);
            continue;
        }
        int found = 0;
        for (int i = 0; i < namesMap; i++) {
            if (strcmp(names[i], line) == 0) {
                occurence[i]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(names[namesMap], line);
            occurence[namesMap] = 1;
            namesMap++;
        }
        ++lineCounter;
    }
    fclose(file);
    
    int len;
    for (int i = 0; i < namesMap; i++) { 
        len = strlen(names[i]);
        names[i][--len] = '\0';
        fprintf(stdout, "%s: %d\n", names[i], occurence[i]);
    }

    return 0;
}
