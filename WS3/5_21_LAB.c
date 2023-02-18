/**
 * Description: 5.21.1: LAB: Contains the character: The code promts the user for an integer, a list of words,
 *    and a character, then outputs all the word in the list that contains the given character at least once
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/16/2023
 * Creation date: 2/13/2023
 **/
#include <stdio.h>
#include <string.h>

int main(void) {

   int MAX_SIZE = 20;
   int INPUT_SIZE = 10;
   char userValues[MAX_SIZE][INPUT_SIZE];

   int arrSize;
   char input[10];
   scanf("%d", &arrSize);
   for (int i = 0; i < arrSize; ++i){
      scanf("%s", input);
      strcpy(userValues[i], input);
   }

   char target;
   scanf(" %c", &target);

   for (int i = 0; i < arrSize; i++){
      for (int j = 0; j < sizeof(userValues[i]); j++){
         if (target == userValues[i][j]){
            printf("%s,", userValues[i]);
            break;
         }
      }
   }

   printf("\n");
   return 0;
}
