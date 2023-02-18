/**
 * Description: 5.22.1: LAB: Elements in a range: This code prompts the user for an int of size of inputs,
 *    then inputs a list of intgers followed by two integers that will be used to hold the bounds,
 *    then it outputs the numbers inside the bounds
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/16/2023
 * Creation date: 2/13/2023
 **/
#include <stdio.h>

int main(void) {

   int MAX_SIZE = 20;
   int userValues[MAX_SIZE];

   int arrSize;
   scanf("%d", &arrSize);
   int input;
   for (int i = 0; i < arrSize; ++i){
        scanf("%d", &input);
        userValues[i] = input;
   }

   int low;
   int high;
   scanf("%d", &low);
   scanf("%d", &high);

   for (int i = 0; i < arrSize; ++i){
      int value = userValues[i];
      if (value >= low && value <= high){
         printf("%d,", value);
      }
   }
   printf("\n");

   return 0;
}
