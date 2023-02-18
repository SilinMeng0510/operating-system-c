/**
 * Description: 4.16.1: LAB: Varied amount of input data: This code takes integer inputs from the user until -1
 *    is inputted, then outputs the maximum number and average
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 2/16/2023
 * Creation date: 2/13/2023
 **/
 #include <stdio.h>

int main(void) {

   int userInput;
   int sum = 0;
   int max = 0;
   int loop = 1;
   int i = 0;
   while(loop){
      scanf("%d",&userInput);
      if(userInput <= -1){
         loop = 0;
         break;
      }
      if(max < userInput){
         max = userInput;
      }
      sum = sum + userInput;
      i++;
   }
   double average = (double)sum / (double)i;
   printf("%d %0.2lf\n", max, average);


   return 0;
}
