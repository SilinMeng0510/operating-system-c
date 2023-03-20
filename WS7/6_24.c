/**
 * Description: 6.24.1: LAB: Swapping variables: This code uses the SwapValeus function which takes 
 *    4 parameters and swaps thier variables to swap 4 inputted integers from the user
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 3/17/2023
 * Creation date: 3/18/2023
 **/
#include <stdio.h>
/**
 * This function swaps 4 integers by reference 
 * Assumption: parameters are valid pointers to integers
 * Input parameters:  userVal1(int*), userVal2(int*), userVal3(int*), userVal4(int*)
 * Returns: nothing
**/
void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4){
   
   int tmp = *userVal1;
   *userVal1 = *userVal2;
   *userVal2 = tmp;
   
   tmp = *userVal3;
   *userVal3 = *userVal4;
   *userVal4 = tmp;
   
}

int main(void) {

   int userInput1,userInput2, userInput3, userInput4;
   
   scanf("%d %d %d %d", &userInput1, &userInput2, &userInput3, &userInput4);
   SwapValues(&userInput1, &userInput2, &userInput3, &userInput4);
   printf("%d %d %d %d\n", userInput1,userInput2, userInput3, userInput4);
   
   

   return 0;
}
