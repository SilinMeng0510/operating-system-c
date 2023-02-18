/**
 * Description: 4.14.1: LAB: Convert to reverse binary: This code prompts the user for an integer and
 *    then converts the input to a reversed binary
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/16/2023
 * Creation date: 2/13/2023
 **/
#include <stdio.h>

int main(void) {

   int userInput;
   scanf("%d", &userInput);
   char binary[100];
   int i = 0;
   while(userInput > 0){
      binary[i] = (userInput % 2) + '0';
      userInput /= 2;
      i++;
   }
   printf("%s\n", binary);
   return 0;
}
