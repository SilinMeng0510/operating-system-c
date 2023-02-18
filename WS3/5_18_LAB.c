/**
 * Description: 5.18.1: LAB: Output values below an amount: This code prompts the user for int for the amount
 *    of inputs there will be then takes the user inputs, and ends the inputs with the maximum amount,
 *    then displays all the values below that maximum amount
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/16/2023
 * Creation date: 2/13/2023
 **/
#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 20;
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user

   int arrSize;
   int userInput;
   scanf("%d", &arrSize);
   for (int i = 0; i < arrSize; ++i){
      scanf("%d", &userInput);
      userValues[i] = userInput;
   }

   int target;
   scanf("%d", &target);
   for (int i = 0; i < arrSize; ++i){
      if (userValues[i] < target){
         printf("%d,", userValues[i]);
      }
   }
   printf("\n");

   return 0;
}
