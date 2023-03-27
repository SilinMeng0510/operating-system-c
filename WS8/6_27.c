/**
 * Description: 6.27.1: LAB: Count characters - functions: This code uses CalcNumCharaters function to determine the
 *    occurance of a character in a string that the user inputs, then outputs occurance and the character followed by 's if plural
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 3/27/2023
 * Creation date: 3/27/2023
 **/
#include <stdio.h>
#include <string.h>

/**
 * This function counts the occurance of a character in a string
 * Assumption: both inputs are terminated by a null character
 * Input parameters: userString(char*), userChar(char)
 * Returns: count(the occurance of the character)
**/
int CalcNumCharacters(char* userString, char userChar){
   int count = 0;
   for(int i = 0; i < strlen(userString); i++){
      if(userString[i] == userChar){
         count++;
      }
   }
   return count;
}

int main(void) {
   char userChar;
   char userInput[50];
   scanf("%c %s", &userChar, userInput);
   
   int charCount = CalcNumCharacters(userInput, userChar);
   
   if(charCount == 1){
      printf("%d %c\n", charCount, userChar);
   }
   else{
      printf("%d %c's\n", charCount, userChar);
   }

   return 0;
}