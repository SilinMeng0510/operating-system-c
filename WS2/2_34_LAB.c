/**
 * Description: 2.34.1: LAB: Input: Welcome message, This code prompts the user for a name then outputs a welcome message with the name"
 * Author names:Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/6/23
 * Creation date: 2/6/23
 **/
#include <stdio.h>

int main(void) {
   char userName[50];

   scanf("%s", userName);
   printf("Hello %s, and welcome to CS Online!\n", userName);

   return 0;
}
