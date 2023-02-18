/**
 * Description: 5.16.1: LAB: Output numbers in reverse: This creates a loop of the size of the first inputted integer,
 *    then loops the user propmted integer in reverse order using an array
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/16/2023
 * Creation date: 2/13/2023
 **/
#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 20;         // Number of input integers
   int userVals[NUM_ELEMENTS];          // Array to hold the user's input integers

   int arrSize;
   int userInput;
   scanf("%d", &arrSize);
   for(int i = 0; i < arrSize; i++){
      scanf("%d", &userInput);
      userVals[i] = userInput;
   }
   for(int i = arrSize - 1; i >= 0; i--){
      printf("%d,", userVals[i]);
   }
   printf("\n");

   return 0;
}
