/**
 * Description: 9.5.1: LAB: Warm up: Parsing strings: This userinputs until q is inputted and while ther user inputs
 *    the code looks for a comma, if there is a comma, the code splits the word before the comma and after and output them
 *    if the userInput doesnt contain a comma, it outputs Error: No comma in string
 * Author names: Silin Meng, Ibrahim Dobashi
 * Author emails: silin.meng@sjsu.edu, ibrahim.dobashi@sjsu.edu
 * Last modified date: 3/31/2023
 * Creation date: 3/31/2023
 **/
#include<stdio.h>
#include <string.h>

int main(void) {
   char userInput[100];
   char firstWord[50];
   char secondWord[50];
   while(1){
      printf("Enter input string:\n");
      fgets(userInput, sizeof(userInput), stdin);
      if (userInput[0] == 'q') {
         break;
      }
      int j = 0;
      int k = 0;
      char comma = 0;
      for(int i = 0; i < strlen(userInput); i++){
         if(userInput[i] == ','){
            comma = 1;
         }
         else if(!comma && userInput[i] != ' '){
            firstWord[j] = userInput[i];
            j++;
         }
         else if(comma && userInput[i] != ' '){
            secondWord[k] = userInput[i];
            k++;
         }
      }
      if(!comma){
         printf("Error: No comma in string.\n\n");
         continue;
      }
      else{
         firstWord[j] = '\0';
         secondWord[k] = '\0';
         printf("First word: %s\n", firstWord);
         printf("Second word: %s\n", secondWord);
      }
       
   }

   return 0;
}