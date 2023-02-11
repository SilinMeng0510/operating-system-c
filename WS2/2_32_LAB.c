/**
 * Description: 2.32.1: LAB: Input and formatted output: House real estate summary, This code prompts the user for two values then outputs the change of those two values and the monthly mortage"
 * Author names:Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/6/23
 * Creation date: 2/6/23
 **/
#include <stdio.h>

int main(void) {
   int currentPrice;
   int lastMonthsPrice;

   scanf("%d", &currentPrice);
   scanf("%d", &lastMonthsPrice);

   printf("This house is $%d. The change is $%d since last month.\n", currentPrice, currentPrice - lastMonthsPrice);
   printf("The estimated monthly mortgage is $%lf.\n", (currentPrice * 0.051) / 12);


   return 0;
}
