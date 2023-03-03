/**
 * Description: 5.26.1: LAB: Count input length without spaces, periods, exclamation points, or commas: 
 *    This code prompmts the user for a string, then in a for loop, checks if there are spaces, periods, exclamation points,
 *    or commas and incremants their count, then ouputs the length of the string - the count of spaces, periods etc
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 3/2/2023
 * Creation date: 3/2/2023
 **/
#include <stdio.h>
#include <string.h>

int main(void) {
   
   char userInput[100];
   
   fgets(userInput, 100, stdin);
   int count = 0;
   for(int i = 0; i < strlen(userInput); i++){
     if ((userInput[i] == '.') || (userInput[i] == ',') || (userInput[i] == ' ') || (userInput[i] == '!')) {
         count++;  
     }
   }
   int finalResult = strlen(userInput) - count;
   printf("%d\n", finalResult);
   return 0;
}

