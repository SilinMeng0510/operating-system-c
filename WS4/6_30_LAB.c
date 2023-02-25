/**
 * Description: 6.30.1: LAB: Write a program whose inputs are four integers, 
 *    and whose outputs are the maximum and the minimum of the four values.
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/24/2023
 * Creation date: 2/24/2023
 **/

#include <stdio.h>
#include <limits.h>

/**
 * This function takes four integers as parameters,
 * and calculate the maximum number returning it
**/ 
int MaxNumber(int num1, int num2, int num3, int num4){
   int max = INT_MIN;
   int num[4] = {num1, num2, num3, num4};
   for(int i = 0; i < 4; ++i){
      if (num[i] > max){
         max = num[i];
      }
   }
   return max;
}

/**
 * This function takes four integers as parameters,
 * and calculate the minumum number returning it
**/
int MinNumber(int num1, int num2, int num3, int num4){
   int min = INT_MAX;
   int num[4] = {num1, num2, num3, num4};
   for(int i = 0; i < 4; ++i){
      if (num[i] < min){
         min = num[i];
      }
   }
   return min;
}

int main(void) {

   int num1, num2, num3 ,num4;
   scanf("%d %d %d %d", &num1, &num2, &num3, &num4);
   printf("Maximum is %d\n", MaxNumber(num1, num2, num3, num4));
   printf("Minimum is %d\n", MinNumber(num1, num2, num3, num4));

   return 0;
}

