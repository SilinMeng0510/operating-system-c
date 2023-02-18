/**
 * Description: 5.17.1: LAB: Middle item: This code takes user inputs until -1 is inputted,
 *    then finds and outputs the middle item using a while loop
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/16/2023
 * Creation date: 2/13/2023
 **/
#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 9;
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user

   int numInput;
   int arrSize = 0;
   scanf("%d", &numInput);
   while (numInput > -1) {
      userValues[arrSize] = numInput;
      scanf("%d", &numInput);
      arrSize++;
   }
   if (arrSize > 9){
      printf("Too many numbers\n");
      return 0;
   }
   printf("Middle item: %d\n", userValues[arrSize / 2]);

   return 0;
}
