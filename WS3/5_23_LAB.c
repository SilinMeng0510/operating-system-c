/**
 * Description: 5.23.1: LAB: Two smallest numbers: The codes prompts the user for integer to represpent how
 *    many inputs there will be followed the list of integers, then using for loops,
 *    calculates and outputs the two smallest integers in the list
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/16/2023
 * Creation date: 2/13/2023
 **/
#include <stdio.h>
#include <limits.h>

int main(void) {

   int userInput[20];

   int arrSize;
   int input;
   scanf("%d", &arrSize);
   for (int i = 0; i < arrSize; ++i){
      scanf("%d", &input);
      userInput[i] = input;
   }
   int min1 = INT_MAX;
   int min2;

   for (int i = 0; i < arrSize; ++i){
      int value = userInput[i];
      if (value < min1){
         min2 = min1;
         min1 = value;
      }
      else if (value < min2){
         min2 = value;
      }
   }

   printf("%d and %d\n", min1, min2);

   return 0;
}
