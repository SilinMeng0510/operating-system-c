/**
 * Description: 1.19 LAB pratice, practice with output in variables
 * Author names:Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/1/23
 * Creation date: 1/30/23
 **/
#include <stdio.h>

int main(void) {
   int userNum;
   int anoNum;

   printf("Enter integer:\n");
   scanf("%d", &userNum);
   printf("You entered: %d\n", userNum);
   printf("%d squared is %d\n", userNum, userNum * userNum);
   printf("And %d cubed is %d!!\n", userNum, userNum * userNum * userNum);
   printf("Enter another integer:\n");
   scanf("%d", &anoNum);
   printf("%d + %d is %d\n", userNum, anoNum, userNum + anoNum);
   printf("%d * %d is %d\n", userNum, anoNum, userNum * anoNum);

   return 0;
}
