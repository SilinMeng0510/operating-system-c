/**
 * Description: 1.17 LAB pratice, printing a arrow sign
 * Author names:Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/1/23
 * Creation date: 1/30/23
 **/
#include <stdio.h>

int main(void) {
   int baseInt;
   int headInt;
   scanf("%i", &baseInt);
   scanf("%i", &headInt);

   printf("    %i\n", headInt);
   printf("    %i%i\n", headInt, headInt);
   printf("%i%i%i%i%i%i%i\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt);
   printf("%i%i%i%i%i%i%i%i\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt, headInt);
   printf("%i%i%i%i%i%i%i\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt);
   printf("    %i%i\n", headInt, headInt);
   printf("    %i\n", headInt);


   return 0;
}
