/**
 * Description: 5.27.1: LAB: Print string in reverse: This code takes a userinputs using fget until 
 *    Done or done or d is inputted then removes the new line value with a null vaule to create a c 
 *    string and in a for loop reverses the string and outputs it
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 3/9/2023
 * Creation date: 3/9/2023
 **/
 
#include <stdio.h>
#include <string.h>

int main() {
    char userInput[51]; 
    while (1) {
        fgets(userInput, 51, stdin); 
        userInput[strcspn(userInput, "\n")] = '\0'; 
        if (strcmp(userInput, "Done") == 0 || strcmp(userInput, "done") == 0 || strcmp(userInput, "d") == 0) {
            break;
        }
        int len = strlen(userInput);
        for (int i = len - 1; i >= 0; i--) { 
            printf("%c", userInput[i]); 
        }
        printf("\n");
    }
    return 0;
}
