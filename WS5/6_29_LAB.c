/**
 * Description: 6.29.1: LAB: Convert to binary - functions: This code converts an integer input from the user 
 *    into the binary equivalent in reverse order using two functions, the IntToReverseBinary() function and the 
 *    StringReverse() function. The binary value is then passed to the StringReverse() function to reverse the 
 *    order of the binary digits and stored in the final character array. Then the code ouputs the final full binary number.
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 3/2/2023
 * Creation date: 3/2/2023
 **/
#include <stdio.h>
#include <string.h>

/**
 * This function converts intger to a binary 
 * Assumption: integer is positive
 * Input parameters: intgerValue(int), binaryValue(char array)
 * Returns: nothing
**/
void IntToReverseBinary(int integerValue, char binaryValue[]){
   int i = 0;
   while(integerValue > 0){
      binaryValue[i] = (integerValue % 2) + '0';       
      integerValue /= 2;
      i++;
   }
   return;
}

/**
 * This function reverses a string 
 * Assumption: string is null terminated 
 * Input parameters: inputString (char array), reversedString (char array)
 * Returns: nothing
**/
void StringReverse(char inputString[], char reversedString[]){
   int j = 0;
   for(int i = strlen(inputString) - 1; i >= 0; i--){
      reversedString[j] = inputString[i];
      j++;
   }
   return;
}

int main(void) {


   int userInput;
   scanf("%d", &userInput);
   char binary[100];
   char final[100];
   IntToReverseBinary(userInput, binary);
   StringReverse(binary, final);
   printf("%s\n", final);
   return 0;
}


