/**
 * Description: 2.25.1: LAB: Divide by x, This code prompts the user for two intgers then outputs the divison of both 3 times"
 * Author names:Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/6/23
 * Creation date: 2/6/23
 **/

#include <stdio.h>

int main(void) {


   int userNum ;
   int x;
   int answer;
   scanf("%d %d", &userNum, &x);
   answer = userNum / x;
   printf("%d %d %d\n", answer, answer / x, (answer / x) / x);



   return 0;
}
